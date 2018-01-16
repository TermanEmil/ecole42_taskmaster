#include "process42.h"

t_rostr	get_proc_state_str(const t_process *proc)
{
	switch (proc->status.state)
	{
		case (e_not_started):
			return STATE_NOT_STARTED;
		case (e_running):
			return STATE_RUNNING;
		case (e_completed):
			return STATE_COMPLETED;
		case (e_stopped):
			return STATE_STOPPED;
		case (e_critic):
			return STATE_CRITIC;
	}
	// if (proc->status.state == e_not_started)
	// 	return STATE_NOT_STARTED;
	// else if (proc->status.state == e_completed)
	// 	return STATE_CRITIC;
	// else if 
	// {
	// 	if (proc->status.attempt >= proc->config->restart_attempts && 
	// 		proc_has_to_be_restarted(proc, proc->status.waitpid_status, FALSE))
	// 		return STATE_CRITIC;
	// 	else
	// 		return STATE_COMPLETED;
	// }
	// else if (proc->status.stopped)
	// 	return STATE_STOPPED;
	// else
	// 	return STATE_RUNNING;
}
