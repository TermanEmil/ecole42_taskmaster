#include "process42.h"

t_lst_proc	*get_processes_from_strcmd(const t_lst_proc *procs, t_rostr cmd)
{
	t_lst_proc	*buf;
	t_process	*proc;

	if ((proc = lst_get_proc_with_pidname(procs, cmd)) != NULL)
	{
		buf = ft_lstnew_nocpy(proc, sizeof(*proc));
		return buf;
	}
	return lst_get_procs_matching_name(procs, cmd);
}
