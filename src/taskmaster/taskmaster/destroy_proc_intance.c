#include "taskmaster42.h"
#include <signal.h>

/*
** Kill and remove any trace of the given process from taskmaster.
*/

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
		(t_lst_cont_cmp*)&proc_ref_equ);

	ft_bzero(buf, sizeof(buf));
	ft_sprintf(buf, "Destroyed %s.", proc->name);
	if (matching)
		ft_lstrm(&taskmast->procs, matching, (t_ldel_func*)&del_proc);
	TASKMAST_LOG(buf, "");
}
