#include "process42.h"

static int	proc_name_cmp_(t_rostr name, t_process *proc)
{
	return ft_strequ(proc->name, name);
}

t_process	*lst_get_proc_with_name(const t_lst_proc* procs, t_rostr name)
{
	t_list	*match;

	match = ft_lst_first(procs, name, ft_strlen(name) + 1,
		(t_lst_cont_cmp*)&proc_name_cmp_);
	return (match == NULL) ? NULL : LCONT(match, t_process*);
}
