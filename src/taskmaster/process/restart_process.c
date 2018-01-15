#include "taskmaster42.h"
#include <signal.h>

int			restart_process(t_process *proc)
{
	if (proc->status.stopped)
		kill(proc->pid, SIGKILL);

	close_process_open_fds(proc);
	proc->status.started = FALSE;
	proc->status.completed = FALSE;
	proc->status.stopped = FALSE;
	ft_bzero(&proc->proc_time, sizeof(proc->proc_time));
	process_start(proc);
	return 0;
}
