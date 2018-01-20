#include "taskmaster42.h"

void			deactivate_schedule(t_alrm_schedl *schedule)
{
	schedule->active = FALSE;
}
