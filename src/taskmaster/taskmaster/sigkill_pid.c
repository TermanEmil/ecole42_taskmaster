#include "taskmaster42.h"
#include <signal.h>

void		sigkill_pid(t_taskmast *taskmaster, pid_t pid)
{
	t_process	*proc;
	t_lst_proc	*match;

	if (pid <= 1)
		return;

	proc = lst_process_pidof(taskmaster->procs, pid);
	if (proc)
	{
		kill_proc(SIGKILL, proc);		
	}
}
