#include "taskmaster42.h"
#include <sys/wait.h>
#include <time.h>

static void	update_proc_stats_(t_process *proc, int waitpid_status)
{
	proc->proc_time.running_time = proc_uptime(proc);
	proc->proc_time.finish_time = time(NULL);
	proc->status.waitpid_status = waitpid_status;
	proc->status.state = e_stopped;
}

void		process_stopped(t_process *proc, int status)
{
	TASKMAST_LOG("Process %s, pid: %d stopped with the signal %d.\n",
		proc->name, proc->pid, WSTOPSIG(status));
	if (ISSTATE(proc, e_grace_stopping))
		return;

	update_proc_stats_(proc, status);
}
