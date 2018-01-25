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
		case (e_grace_stopping):
			return STATE_GRACE_STOP;
	}
	return NULL;
}
