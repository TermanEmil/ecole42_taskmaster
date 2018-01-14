#include "process42.h"
#include <time.h>

int		proc_uptime(const t_process *proc)
{
	int		elapsed_time;

	if (!proc->status.started)
		return 0;
	else if (proc->status.stopped || proc->status.completed)
		return proc->proc_time.running_time;
	else
	{
		return time(NULL) - proc->proc_time.start_time +
			proc->proc_time.running_time;
	}
}
