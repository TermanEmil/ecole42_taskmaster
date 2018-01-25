#include "taskmaster42.h"
#include <sys/types.h>
#include <signal.h>
#include <time.h>

void			remove_dead_pid_schedule_(t_alrm_schedl *schedule)
{
	t_process	*proc;

	if (kill(schedule->pid, 0) == -1)
	{
		errno = 0;
		proc = lst_proc_pidof_grac_stop(g_taskmast.procs, schedule->pid);
		remove_schedule(schedule);
		if (proc)
			destroy_proc_intance(&g_taskmast, proc);
	}
}

static void		get_proc_and_next_schedl_(
					t_lst_schedl **schedules,
					t_process **proc,
					t_alrm_schedl **schedl_result)
{
	do
	{
		ft_lstiter_mem(g_taskmast.schedules,
			(void (*)(void*))&remove_dead_pid_schedule_);
		*schedl_result = get_min_time_schedule(*schedules);
		if (*schedl_result == NULL)
			break;
		*proc = lst_process_pidof(g_taskmast.procs, (*schedl_result)->pid);
	} while (proc == NULL);
}

static int		actual_alarm_set_(t_alrm_schedl *next_schedule, t_process *proc)
{
	int	dif;

	dif = next_schedule->tm - time(NULL);
	if (dif <= 0)
	{
		next_schedule->f(&g_taskmast, proc->pid);
		remove_schedule(next_schedule);
		g_taskmast.next_schedl = NULL;
		return -1;		
	}
	else
	{
		g_taskmast.next_schedl = next_schedule;
		alarm((unsigned int)dif);
		return 0;
	}
}

void			update_alarm()
{
	t_alrm_schedl	*next_schedule;
	t_process		*proc;

	get_proc_and_next_schedl_(&g_taskmast.schedules, &proc, &next_schedule);

	if (next_schedule == NULL)
	{
		g_taskmast.next_schedl = NULL;
		return;
	}
	if (g_taskmast.next_schedl == next_schedule)
		return;

	if (actual_alarm_set_(next_schedule, proc) == -1)
		update_alarm();
}
