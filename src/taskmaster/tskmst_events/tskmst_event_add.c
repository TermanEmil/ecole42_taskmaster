#include "tskmst_events.h"

/*
** Signal safe event add.
*/

void		tskmst_event_add(
				t_event_ctrl *event_ctrl,
				int time,
				pid_t target_pid,
				void (*handler)(pid_t, int time))
{
	t_lst_tskevent	*free_event_inst;
	t_tskmst_event	*event;

	do
	{
		free_event_inst = tskmst_get_free_event_inst(event_ctrl->events_buf, 1);
		if (free_event_inst == NULL)
		{
			tskmst_event_extend_buf(event_ctrl,
				ft_lstlen(event_ctrl->events_buf));
		}

		event = LCONT(free_event_inst, t_tskmst_event*);
	} while (event->target_pid == -1);
	event->time = time;
	event->target_pid = target_pid;
	event->handler = handler;
}
