#include "taskmaster42.h"
#include <signal.h>

/*
** Kill and remove any trace of the given process from taskmaster.
*/

void		destroy_proc_intance(t_taskmast *taskmast, t_process *proc)
{
	t_lst_proc	*matching;
	char		buf[124];

	if (ISSTATE(proc, e_running) || ISSTATE(proc, e_stopped) ||
		ISSTATE(proc, e_grace_stopping))
	{
		proc->status.attempt = INT_MAX;
		if (ISSTATE(proc, e_grace_stopping))
			kill_proc(SIGKILL, proc);
		else
			proc_graceful_stop(proc);
	}

	close_process_open_fds(proc);
	matching = ft_lst_first(taskmast->procs, proc, 0,
		(t_lst_cont_cmp*)&proc_ref_equ);

	ft_bzero(buf, sizeof(buf));
	ft_sprintf(buf, "Destroyed %s.\n", proc->name);
	if (matching)
		ft_lstrm(&taskmast->procs, matching, (t_ldel_func*)&del_proc);
	TASKMAST_LOG(buf, "");
}
