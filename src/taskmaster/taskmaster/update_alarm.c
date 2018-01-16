#include "taskmaster42.h"
#include <signal.h>

static void			kill_proc_(const t_process *proc)
{
	if (proc->pid < 0)
		return;

	if (kill(proc->pid, SIGKILL) == -1)
	{
		if (errno != ESRCH)
		{
			TASKMAST_ERROR(FALSE, "update_alarm(): kill(): %s\n",
				strerror(errno));
		}
		errno = 0;
	}
	else
		taskmast_log_kill_exceed_time(proc);
}

static t_process	*get_closest_proc_to_kill_(const t_lst_proc *procs)
{
	int				min_dif;
	int				dif;
	t_process		*target_proc;
	t_process		*proc;

	min_dif = INT_MAX;
	target_proc = NULL;
	for (; procs; LTONEXT(procs))
	{
		proc = LCONT(procs, t_process*);
		if (proc->config->time_before_kill < 0 || !ISSTATE(proc, e_running))
			continue;

		dif = proc->config->time_before_kill - proc_uptime(proc);
		if (dif <= 0)
			kill_proc_(proc);
		else if (dif < min_dif)
		{
			min_dif = dif;
			target_proc = proc;
		}
	}
	return target_proc;
}

void				update_alarm()
{
	t_process	*next_to_alarm;
	int			dif;

	next_to_alarm = get_closest_proc_to_kill_(g_taskmast.procs);
	if (next_to_alarm == NULL || next_to_alarm == g_taskmast.next_alarm)
		return;

	dif = next_to_alarm->config->time_before_kill - proc_uptime(next_to_alarm);
	g_taskmast.next_alarm = next_to_alarm;
	TASKMAST_LOG("Setting alaram for %s\n", next_to_alarm->name);
	alarm((unsigned int)dif);
}
