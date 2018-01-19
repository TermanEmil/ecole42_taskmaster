#include "taskmaster42.h"

void		signaled_flags_set_signaled(t_taskmast *taskmaster)
{
	int		i;

	for (i = 0; i < SIGNALED_FLAGS_COUNT; i++)
		taskmaster->signaled_flags[i].signaled = TRUE;
}
