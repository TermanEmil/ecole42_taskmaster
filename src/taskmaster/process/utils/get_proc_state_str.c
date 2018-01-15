#include "process42.h"
// #include "libft.h"

t_rostr	get_proc_state_str(const t_process *proc)
{
	if (!proc->status.started)
		return STATE_NOT_STARTED;
	else if (proc->status.completed)
	{
		if (proc->status.attempt >= proc->config->restart_attempts && 
			proc_has_to_be_restarted(proc, proc->status.waitpid_status, FALSE))
			return STATE_CRITIC;
		else
			return STATE_COMPLETED;
	}
	else if (proc->status.stopped)
		return STATE_STOPPED;
	else
		return STATE_RUNNING;
}
