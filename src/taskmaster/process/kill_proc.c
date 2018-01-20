#include "taskmaster42.h"
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/*
** To recieve true log, I must save the log before calling kill.
*/

int		kill_proc(int signum, t_process *proc)
{
	char		buf[124];

	if (proc->pid <= 1)
		return -1;

	ft_bzero(buf, sizeof(buf));
	ft_sprintf(buf, "%s %s, PID: %d, uptime: %s\n\n",
		strsignal(signum), proc->name, proc->pid, proc_struptime(proc));

	TASKMAST_LOG("Sending signal to %s PID %d\n", proc->name, proc->pid);
	if (kill(proc->pid, signum) == -1)
	{
		if (errno != ESRCH)
		{
			TASKMAST_ERROR(FALSE, "kill(): pid = %d, signum = %d: %s",
				proc->pid, signum, strerror(errno));
			errno = 0;
			return -1;
		}
		errno = 0;
	}
	else
		TASKMAST_LOG(buf, "");
	return 0;
}

int			get_grace_stop_proc_name_id(
				t_rostr default_name, const t_lst_proc *procs)
{
	int					max;
	t_rostr				numb_ref;
	const t_lst_proc	*next;
	const t_process		*aux;

	max = 0;
	for (; procs; procs = next)
	{
		next = LNEXT(procs);
		aux = LCONT(procs, t_process*);
		if (aux->active && ft_str_starts_with(aux->name, default_name))
		{
			numb_ref = aux->name + ft_strlen(default_name) + 1;
			if (ft_str_is_numb(numb_ref))
				max = ft_atoi(numb_ref) + 1;
		}
	}
	return max;
}

t_process	new_grace_stop_proc(const t_process *proc)
{
	t_process	result;
	t_str		tmp_name;

	ft_memcpy(&result, proc, sizeof(result));
	tmp_name = ft_strmegajoin(2, proc->name, "_grace_stop");
	result.name_id = get_grace_stop_proc_name_id(tmp_name, g_taskmast.procs);
	result.name = new_process_name(tmp_name, result.name_id);
	ft_memdel((void**)&tmp_name);
	return result;
}

static void	discard_proc_redirs_(t_process *proc)
{
	proc->stdin_fd[0] = -1;
	proc->stdin_fd[1] = -1;
	proc->stdout_fd[0] = -1;
	proc->stdout_fd[1] = -1;
	proc->stderr_fd[0] = -1;
	proc->stderr_fd[1] = -1;
}

void		sigkill_process(t_taskmast *taskmaster, t_process *proc)
{
	(void)taskmaster;
	if (proc->pid <= 1)
		return;
	kill_proc(SIGKILL, proc);
}

void		proc_graceful_stop(t_process *proc)
{
	t_process	stop_proc;

	if (lst_proc_pidof_grac_stop(g_taskmast.procs, proc->pid))
		return;
	stop_proc = new_grace_stop_proc(proc);
	discard_proc_redirs_(proc);

	stop_proc.status.state = e_grace_stopping;
	stop_proc.proc_time.start_time = time(NULL);
	stop_proc.proc_time.running_time = 0;
	stop_proc.proc_time.finish_time = 0;

	ft_lstadd(&g_taskmast.procs, ft_lstnew(&stop_proc, sizeof(stop_proc)));
	TASKMAST_LOG("Graceful stop process: %s PID %d has been set for %s, "
		"which will get sigkilled in %d s\n", stop_proc.name,
		stop_proc.pid, proc->name, stop_proc.config->time_before_forced_kill);	
	
	kill_proc(proc->config->sig_graceful_stop, proc);
	setup_alarm(&g_taskmast,
		new_alarm_schedule(
			stop_proc.pid,
			time(NULL) + stop_proc.config->time_before_forced_kill,
			&sigkill_process));
}