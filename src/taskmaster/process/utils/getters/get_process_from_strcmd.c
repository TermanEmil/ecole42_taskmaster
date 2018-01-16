#include "process42.h"

t_process	*get_process_from_strcmd(const t_lst_proc *procs, t_rostr cmd)
{
	t_process	*proc;

	proc = lst_get_proc_with_pidname(procs, cmd);
	if (proc == NULL)
		proc = lst_get_proc_with_name(procs, cmd);
	return proc;
}
