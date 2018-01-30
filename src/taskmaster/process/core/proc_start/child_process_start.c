#include "taskmaster42.h"
#include "taskmaster42_utils_.h"
#include <sys/stat.h>

static void	ignore_ctrl_c_()
{
	if (setsid() == -1)
		TASKMAST_ERROR(FALSE, "setsid(): %s\n", strerror(errno));
	errno = 0;
}

static void	parse_redirs_(t_process *proc)
{
	close_if_open(&proc->stdin_fd[1]);
	close_if_open(&proc->stdout_fd[0]);
	close_if_open(&proc->stderr_fd[0]);
	dup2_close(proc->stdin_fd[0], STDIN_FILENO);
	dup2_close(proc->stdout_fd[1], STDOUT_FILENO);
	dup2_close(proc->stderr_fd[1], STDERR_FILENO);
	process_std_redir_to_file(proc->config->stdout, STDOUT_FILENO);
	process_std_redir_to_file(proc->config->stderr, STDERR_FILENO);
}

static t_str	*get_argv_(t_rostr cmd)
{
	t_lst_inkey	*cmd_keys;
	t_lst_words	*words;
	t_str		*argv;
	int			ret;

	cmd_keys = get_sh_inkeys_from_str(cmd);
	if ((ret = assign_what_are_insideof(cmd_keys)) != 0)
	{
		if (ret == -1)
		{
			ft_error(FALSE, "%s: cmd isn't complete: an unexpected"
				" delim has been detected\n", cmd);
		}
		else
			ft_error(FALSE, "%s: cmd isn't complete (%c)\n", cmd, ret);
		return NULL;
	}
	words = extract_words_from_keys(cmd_keys);
	argv = words_to_argv(words);
	del_lst_of_words(words);
	ft_lstdel(&cmd_keys, (t_ldel_func*)&sh_inkey_destruct);
	return argv;
}

/*
** I need the real path of the launch command so that if I change directories
** and the launch command is a relative path, it will still work.
*/

static int	parse_real_path_(const t_process *proc, t_str *argv)
{
	char	real_path[PATH_MAX];

	if (realpath(argv[0], real_path) == NULL)
	{
		ft_error(FALSE, "realpath(): %s: %s: %s\n",
			proc->name, argv[0], strerror(errno));
		errno = 0;
		return -1;
	}

	if (!ft_strequ(real_path, proc->config->launch_cmd))
	{
		ft_memdel((void**)&(argv[0]));
		if ((argv[0] = ft_strdup(real_path)) == NULL)
			ft_err_mem(TRUE);
	}
	return 0;
}

static void	set_dfl_(int signum)
{
	if (signal(signum, SIG_DFL) == SIG_ERR)
	{
		TASKMAST_ERROR(FALSE, "signal(): %s\n", strerror(errno));
		errno = 0;
	}
}

void	close_child_trash()
{
	if (pthread_join(g_taskmast.waiter_thread, NULL) != 0 && errno != 0)
		TASKMAST_ERROR(TRUE, "pthread_join(): %s\n", strerror(errno));
	set_dfl_(SIGCHLD);
	set_dfl_(SIGHUP);
	set_dfl_(SIGALRM);
}

void		child_process_start(t_process *proc)
{
	t_str	*env_tab;
	t_str	*argv;

	close_child_trash();
	ignore_ctrl_c_();
	parse_redirs_(proc);
	if ((argv = get_argv_(proc->config->launch_cmd)) == NULL)
		return;
	if (parse_real_path_(proc, argv) != 0)
	{
		ft_free_bidimens(argv);
		return;
	}
	if (proc_mv_to_dir(proc->config->dir) == -1)
		_exit(EXIT_FAILURE);

	if (proc->config->environment)
		env_tab = proc->config->environment;
	else
		env_tab = shvars_form_key_val_tab(g_shdata.shvars.env);

	umask(proc->config->umask);
	execve(argv[0], argv, env_tab);
	ft_prerror(FALSE, "%s: %s\n", argv[0], strerror(errno));
	_exit(EXIT_FAILURE);
}
