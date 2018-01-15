#include "taskmaster42.h"
#include <sys/types.h>
#include <signal.h>

#define STATE_LEN_ 26
#define DESCRIPT_LEN_ 64
#define PROC_NAME_LEN_ 32

static t_rostr	get_atempts_str_(const t_process *proc, t_rostr state_str)
{
	static char	buf[32];
	t_rostr		color;

	ft_bzero(buf, sizeof(buf));
	if (ft_strequ(state_str, STATE_CRITIC))
		color = C_RED;
	else
		color = C_GREEN;
	ft_sprintf(buf, "%s%d/%d" C_EOC,
		color, proc->status.attempt, proc->config->restart_attempts);
	return buf;
}

static t_rostr	get_proc_description_(const t_process *proc, t_rostr state_str)
{
	static char		buf[124];
	int				atempt_dif;
	int				cfg_restarts;

	ft_bzero(buf, sizeof(buf));
	if (ft_strequ(state_str, STATE_NOT_STARTED))
		ft_pass();
	else
	{
		cfg_restarts = proc->config->restart_attempts;
		atempt_dif = cfg_restarts - proc->status.attempt;
		ft_sprintf(buf, "pid: %d, uptime: %s, %s",
			proc->pid, proc_struptime(proc),
			get_atempts_str_(proc, state_str));
	}
	return buf;
}

static void		print_proc_status_(const t_process *proc)
{
	t_rostr		strstate;

	strstate = get_proc_state_str(proc);
	ft_printf("%*s %*s %*s\n",
		STATE_LEN_, strstate,
		DESCRIPT_LEN_, get_proc_description_(proc, strstate),
		PROC_NAME_LEN_, proc->name);
}

static void		print_general_status_(const t_lst_proc *procs)
{
	int				running;
	int				finished;
	int				stopped;
	int				failed;
	int				total;
	t_rostr			proc_state;

	running = 0;
	finished = 0;
	stopped = 0;
	failed = 0;
	total = ft_lstlen(procs);
	for (; procs; LTONEXT(procs))
	{
		proc_state = get_proc_state_str(LCONT(procs, t_process*));
		running += (ft_strequ(proc_state, STATE_RUNNING));
		finished += (ft_strequ(proc_state, STATE_COMPLETED));
		failed += (ft_strequ(proc_state, STATE_CRITIC));
		stopped += (ft_strequ(proc_state, STATE_STOPPED));
	}
	ft_printf(
		"Running: %d, Completed: %d, Critic: %d, Stopped: %d, Total: %d\n",
		running, finished, failed, stopped, total);
}

int				execute_tskmast_cmd_status()
{
	size_t				color_len;

	print_general_status_(g_taskmast.procs);
	color_len = ft_strlen(C_RED) + ft_strlen(C_EOC);
	ft_printf("%*s %*s %*s\n",
		STATE_LEN_ - color_len, "State",
		DESCRIPT_LEN_ - color_len, "Description",
		PROC_NAME_LEN_, "Name");

	ft_lstiter_mem(g_taskmast.procs, (void (*)(void*))&print_proc_status_);
	return 0;
}
