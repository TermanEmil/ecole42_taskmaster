#include "taskmaster42.h"

void	setup_alarm(t_taskmast *taskmast, t_alrm_schedl schedl)
{
	ft_lstadd(&taskmast->schedules, ft_lstnew(&schedl, sizeof(schedl)));
}
