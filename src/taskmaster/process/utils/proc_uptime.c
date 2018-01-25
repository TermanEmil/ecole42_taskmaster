#include "process42.h"
#include <time.h>

int		proc_uptime(const t_process *proc)
{
	if (proc->status.state == e_not_started)
		return 0;
	else if (
			ISSTATE(proc, e_stopped) ||
			ISSTATE(proc, e_completed) ||
			ISSTATE(proc, e_critic)
		)
	{
		return proc->proc_time.running_time;
	}
	else
	{
		return time(NULL) - proc->proc_time.start_time +
			proc->proc_time.running_time;
	}
}
