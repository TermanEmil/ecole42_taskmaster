#include "shell42.h"
#include "taskmaster42.h"
#include "regex_tools.h"
#include "ft_colors.h"
#include "taskmaster42_utils_.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <wait.h>
#include <pthread.h>

t_shdata		g_shdata;
t_shinput		*g_shinput;
t_current_input	*g_current_in;
t_taskmast		g_taskmast;

static t_bool	proc_cfg_hash_equ_(
					const size_t *hash,
					const t_proc_config *config)
{
	return *hash == config->hash;
}

static t_bool	proc_ref_equ_(const t_process *proc1, const t_process *proc2)
{
	return proc1 == proc2;
}

static t_bool	proc_cfg_equ_(
					const t_process *proc,
					const t_proc_config *cfg)
{
	return proc->config->hash == cfg->hash;
}

static t_bool	proc_cfgs_equ_(
					const t_lst_proccfg *proc_cfgs,
					const t_process *proc)
{

	// return ft_lst_first(proc_cfgs, proc, 0, &proc_cfg_equ_) ==;
	return 0;
}

static void	remove_the_same_cfgs_(t_lst_proccfg **current, t_lst_proccfg **new)
{
	t_lst_proccfg	*new_i;
	t_lst_proccfg	*matching;
	t_lst_proccfg	*next;

	for (new_i = *new; new_i;)
	{
		matching = ft_lst_first(*current, &LCONT(new_i, t_proc_config*)->hash,
			0, (t_lst_cont_cmp*)&proc_cfg_hash_equ_);
		if (matching != NULL)
		{
			next = LNEXT(new_i);
			ft_lstrm(current, matching, NULL);
			ft_lstrm(new, new_i, NULL);
			new_i = next;
		}
		else
			LTONEXT(new_i);
	}
}

void		destroy_proc_intance(t_taskmast *taskmast, t_process *proc)
{
	t_lst_proc	*matching;
	char		buf[124];

	if (ISSTATE(proc, e_running) || ISSTATE(proc, e_stopped))
	{
		proc->status.attempt = INT_MAX;
		ft_printf("Killing %s PID %d\n", proc->name, proc->pid);
		kill_proc(SIGKILL, proc);
	}
	if (taskmast->next_alarm == proc)
		taskmast->next_alarm = NULL;

	close_process_open_fds(proc);
	matching = ft_lst_first(taskmast->procs, proc, 0,
		(t_lst_cont_cmp*)&proc_ref_equ_);

	ft_bzero(buf, sizeof(buf));
	ft_sprintf(buf, "Destroyed %s.", proc->name);
	// if (matching)
	// 	ft_lstrm(&taskmast->procs, matching, (t_ldel_func*)&del_proc);
	if (matching)
		ft_lstrm(&taskmast->procs, matching, NULL);
	TASKMAST_LOG(buf, "");
}

void		destroy_procs_with_config(
				t_taskmast *taskmast,
				const t_proc_config *cfg)
{
	t_lst_proc	*next;
	t_lst_proc	*iter;

	for (iter = taskmast->procs; iter;)
	{
		next = LNEXT(iter);
		if (LCONT(iter, t_process*)->config->hash == cfg->hash)
			destroy_proc_intance(taskmast, LCONT(iter, t_process*));
		iter = next;
	}
}

// void		reload_proc_config(
// 				t_taskmast *taskmast,
// 				t_process *proc,
// 				t_proc_config *new_proc_cfg)
// {

// }

void		reload_taskmast_config(
				t_taskmast *taskmast,
				t_lst_proccfg *new_cfgs)
{
	t_lst_proccfg	*proc_cfgs_buf;
	t_lst_proccfg	*new_cfgs_save;
	t_lst_proc		*new_procs_index;

	new_cfgs_save = ft_lstcpy(new_cfgs);
	proc_cfgs_buf = ft_lstcpy(taskmast->proc_cfgs);
	remove_the_same_cfgs_(&proc_cfgs_buf, &new_cfgs);

	ft_printf("%d %d\n", ft_lstlen(proc_cfgs_buf), ft_lstlen(new_cfgs));

	ft_lstiter_mem2(proc_cfgs_buf, taskmast,
		(void (*)(void*, void*))&destroy_procs_with_config);
	
	new_procs_index = ft_lst_get_last(taskmast->procs);
	create_processes(taskmast, new_cfgs);
	ft_lstiter_mem(new_procs_index->next, (void (*)(void*))&process_start);
	ft_lstdel(&taskmast->proc_cfgs, NULL);
	taskmast->proc_cfgs = new_cfgs_save;
}

void		reload_configfile(
				t_taskmast *taskmast,
				const t_shvars *shvars,
				t_rostr file_path)
{
	t_taskmast	dummy_taskmast;

	ft_bzero(&dummy_taskmast, sizeof(dummy_taskmast));
	taskmast_load_all_config(shvars, &dummy_taskmast, file_path);

	if (!ft_strequ(taskmast->logger.log_file_path,
		dummy_taskmast.logger.log_file_path))
	{
		ft_memdel((void**)&taskmast->logger.log_file_path);
		taskmast->logger.log_file_path =
			dummy_taskmast.logger.log_file_path;
		dummy_taskmast.logger.log_file_path = NULL;
		taskmast_setup_logger(taskmast);
	}

	reload_taskmast_config(taskmast, dummy_taskmast.proc_cfgs);
	// ft_lstdel(&dummy_taskmast.proc_cfgs, NULL);
	dummy_taskmast.proc_cfgs = NULL;
	del_taskmast(&dummy_taskmast);
}

int		main(int argc, const char **argv, const char **envp)
{
	init_shell(envp);

	term_restore_to_old_term_data();
	init_taskmaster("./aux/taskmaster.cngf");
	taskmast_start(&g_taskmast);
	term_enable_raw_mode(term_get_data());  

	if (g_shdata.is_term)
	{
		term_putnewl();
		input_reprint_here(g_current_in);
	}

	while (1)
	{
		shinput_reset_signals(g_shinput);
		shell_read_user_input();
		shinput_process_signals(g_shinput);
	}

	event_exit(0);
}
