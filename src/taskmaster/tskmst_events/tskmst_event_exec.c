#include "tskmst_events.h"

void	tskmst_event_exec(t_tskmst_event *event)
{
	event->handler(event->target_pid, event->time);
	event->target_pid = -1;
}
