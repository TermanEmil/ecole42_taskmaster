#include "tskmst_events.h"
#include "ft_errors.h"

static int	init_extender_(
				t_event_ctrl *event_ctrl,
				int count,
				int *initial_count,
				t_tskmst_event *event)
{
	*initial_count = event_ctrl->extend_buf_count;
	if (event_ctrl->extend_lock)
	{
		event_ctrl->extend_buf_count += count + 8;
		return -1;
	}
	event_ctrl->extend_lock = TRUE;

	ft_bzero(event, sizeof(*event));
	event->target_pid = -1;
	return 0;
}

/*
** Signal safe event extend.
*/

void		tskmst_event_extend_buf(t_event_ctrl *event_ctrl, int count)
{
	t_lst_tskevent	*tmp;
	t_tskmst_event	event;
	int				initial_count;

	if (init_extender_(event_ctrl, count, &initial_count, &event) == -1)
		return;

	for (; count > 0; count--)
	{
		if (initial_count < event_ctrl->extend_buf_count)
		{
			count += event_ctrl->extend_buf_count - initial_count;
			initial_count = event_ctrl->extend_buf_count;
		}

		if ((tmp = ft_lstnew(&event, sizeof(event))) == NULL)
			ft_err_mem(TRUE);

		ft_lstadd(&event_ctrl->events_buf, tmp);
		event_ctrl->extend_lock = FALSE;
	}
	event_ctrl->extend_buf_count = 0;
	event_ctrl->extend_lock = FALSE;
}
