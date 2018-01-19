#include "taskmaster42.h"

t_signaled_flg	*get_free_signaled_flg_entry(const t_taskmast *taskmast)
{
	int		i;

	for (i = 0; i < SIGNALED_FLAGS_COUNT; i++)
		if (!taskmast->signaled_flags[i].is_occupied)
			return (t_signaled_flg*)&(taskmast->signaled_flags[i]);
	TASKMAST_ERROR(TRUE,
		"get_free_signaled_flg_entry(): no free signal flag\n", "");
	return NULL;
}
