#include "tskmst_events.h"

t_lst_tskevent	*tskmst_get_free_event_inst(t_lst_tskevent *events, int count)
{

	for (events; events; LTONEXT(events))
		if (LCONT(events, t_tskmst_event*)->target_pid == -1)
		{
			count--;
			if (count <= 0)
				return events;
		}
	return NULL;
}
