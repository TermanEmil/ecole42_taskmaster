#include "taskmaster42.h"

void		process_continue(t_process *proc, int status)
{
	TASKMAST_LOG("Process %s, pid: %d continued.\n", proc->name, proc->pid);
	if (ISSTATE(proc, e_grace_stopping))
		return;
	proc->status.waitpid_status = status;
	proc->proc_time.start_time = time(NULL);
	proc->status.state = e_running;
}
