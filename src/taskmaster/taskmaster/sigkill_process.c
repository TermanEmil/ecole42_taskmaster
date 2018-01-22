#include "taskmaster42.h"
#include <signal.h>

void		sigkill_process(t_taskmast *taskmaster, t_process *proc)
{
	(void)taskmaster;
	if (proc->pid <= 1)
		return;
	kill_proc(SIGKILL, proc);
	deactivate_process(proc);
}
