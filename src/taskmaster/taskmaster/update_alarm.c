#include "taskmaster42.h"
#include <sys/types.h>
#include <signal.h>

static int		schedule_get_time_(const t_alrm_schedl *schedule)
{
	return schedule->tm;
}

static void		remove_dead_pid_schedules_(
					t_lst_schedl **schedules)
{
	t_lst_schedl	*next;
	t_lst_schedl	*iter;
	t_alrm_schedl	*schedule;
	t_process		*proc;
	t_signaled_flg	*signaled_flg;

	signaled_flg = get_free_signaled_flg_entry(&g_taskmast);
	signaled_flg->is_occupied = TRUE;
	signaled_flg->signaled = FALSE;
	for (iter = *schedules; iter; iter = next)
	{
		if (signaled_flg->signaled)
		{
			TASKMAST_LOG("Interrupt in loop\n", "");
			break;
		}
		next = LNEXT(iter);
		schedule = LCONT(iter, t_alrm_schedl*);
		if (kill(schedule->pid, 0) == -1)
		{
			errno = 0;
			proc = lst_proc_pidof_grac_stop(g_taskmast.procs, schedule->pid);
			if (proc)
				destroy_proc_intance(&g_taskmast, proc);

			ft_lstrm(schedules, iter, &std_mem_del);
		}
	}
	signaled_flg->is_occupied = FALSE;
}

static void		get_proc_and_next_schedl_(
					const t_lst_proc *procs,
					t_lst_schedl **schedules,
					t_process **proc,
					t_lst_schedl **next_schedule_lst)
{
	t_alrm_schedl *next_schedule;

	do
	{
		remove_dead_pid_schedules_(&g_taskmast.schedules);
		*next_schedule_lst = ft_lst_min(g_taskmast.schedules,
			(int (*)(void*))&schedule_get_time_);
		if (*next_schedule_lst == NULL)
			break;
		next_schedule = LCONT(*next_schedule_lst, t_alrm_schedl*);
		*proc = lst_process_pidof(g_taskmast.procs, next_schedule->pid);
	} while (proc == NULL);
}

static int		actual_alarm_set_(
					t_lst_schedl *match_schedule,
					t_alrm_schedl *next_schedule,
					t_process *proc)
{
	int	dif;

	dif = next_schedule->tm - time(NULL);
	if (dif <= 0)
	{
		next_schedule->f(&g_taskmast, proc);
		ft_lstrm(&g_taskmast.schedules, match_schedule, &std_mem_del);
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
	t_lst_schedl	*match;
	t_process		*proc;
	int				dif;

	get_proc_and_next_schedl_(
		g_taskmast.procs, &g_taskmast.schedules, &proc, &match);
	next_schedule = (match == NULL) ? NULL : LCONT(match, t_alrm_schedl*);

	if (next_schedule == NULL)
	{
		g_taskmast.next_schedl = NULL;
		return;
	}
	if (g_taskmast.next_schedl == next_schedule)
		return;

	if (actual_alarm_set_(match, next_schedule, proc) == -1)
		update_alarm();
}
