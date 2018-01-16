#include "process42.h"

/*
** List util.
*/

t_bool	proc_is_state(enum e_proc_state *state, const t_process *proc)
{
	return ISSTATE(proc, *state);
}
