#include "taskmaster42.h"

void		taskmast_log_kill_exceed_time(const t_process *proc)
{
	TASKMAST_LOG("Killed %s PID: %d for: exceeding time_before_kill\n",
		proc->name, proc->pid);
}
