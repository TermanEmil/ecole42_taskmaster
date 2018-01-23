#include "taskmaster42.h"

void			remove_schedule(t_alrm_schedl *schedule)
{
	t_lst_schedl	*match;

	match = ft_lst_first(g_taskmast.schedules, schedule, sizeof(schedule),
		&std_lst_cont_ptr_cmp);

	if (match)
		ft_lstrm(&g_taskmast.schedules, match, &std_mem_del);
}
