#ifndef _TSKMST_EVENTS_H_
# define _TSKMST_EVENTS_H_

# include "listlib.h"

typedef t_list		t_lst_tskevent;

typedef struct		s_tskmst_event
{
	int				time;
	pid_t			target_pid;
	void			(*handler)(pid_t, int time);
}					t_tskmst_event;

typedef struct		s_event_ctrl
{
	t_lst_tskevent	*events_buf;
	int				extend_buf_count;
	t_bool			extend_lock;
}					t_event_ctrl;

t_lst_tskevent	*tskmst_get_free_event_inst(t_lst_tskevent *events, int count);
void			tskmst_event_extend_buf(t_event_ctrl *event_ctrl, int count);
void			tskmst_event_add(t_event_ctrl *event_ctrl, int time,
					pid_t target_pid, void (*handler)(pid_t, int time));
void			tskmst_event_exec(t_tskmst_event *event);

#endif