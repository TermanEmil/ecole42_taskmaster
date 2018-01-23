#include "taskmaster42.h"
#include <sys/types.h>
#include <signal.h>
#include <time.h>

static int		schedule_get_time_(const t_alrm_schedl *schedule)
{
	return schedule->tm;
}

static t_alrm_schedl	*get_min_time_schedule(const t_lst_schedl *schedules)
{
	t_lst_schedl	*lmin;
	t_alrm_schedl	*result;
	t_bool			true_bool;

	if (schedules == NULL)
		return NULL;

	true_bool = TRUE;
	lmin = ft_lst_min(schedules, (int (*)(void*))&schedule_get_time_);
	result = (lmin == NULL) ? NULL : LCONT(lmin, t_alrm_schedl*);
	return result;
}

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
					const t_lst_proc *procs,
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
		next_schedule->f(&g_taskmast, proc);
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

	get_proc_and_next_schedl_(
		g_taskmast.procs, &g_taskmast.schedules, &proc, &next_schedule);

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
