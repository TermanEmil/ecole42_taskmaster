#include "taskmaster42.h"
#include <sys/types.h>
#include <signal.h>

#define STATE_LEN_ 24
#define DESCRIPT_LEN_ 64
#define PROC_NAME_LEN_ 32
#define PID_LEN_ 9

static void		print_proc_status_(const t_process *proc)
{
	t_rostr		strstate;

	strstate = get_proc_state_str(proc);
	ft_printf("%*s %*s %*s %-*d\n",
		STATE_LEN_, strstate,
		DESCRIPT_LEN_, get_proc_description(proc, strstate),
		PROC_NAME_LEN_, proc->name,
		PID_LEN_, proc->pid);
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
	ft_printf("%*s %*s %*s %-*s\n",
		STATE_LEN_ - ft_strlen(C_EOC), C_LMAGENTA "State",
		DESCRIPT_LEN_ - color_len, "Description",
		PROC_NAME_LEN_, "Name",
		PID_LEN_ + ft_strlen(C_LMAGENTA), "PID" C_EOC);

	ft_lstiter_mem(g_taskmast.procs, (void (*)(void*))&print_proc_status_);
	return 0;
}
