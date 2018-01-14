#include "process42.h"
#include "taskmaster42_utils_.h"

t_rostr	proc_struptime(const t_process *proc)
{
	return str_elapsed_time(proc_uptime(proc));
}
