#include "taskmaster42.h"

t_alrm_schedl	new_alarm_schedule(
					pid_t pid,
					int schedule_time,
					void (*f)(t_taskmast*, pid_t))
{
	t_alrm_schedl	result;

	result.pid = pid;
	result.tm = schedule_time;
	result.f = f;
	return result;
}
