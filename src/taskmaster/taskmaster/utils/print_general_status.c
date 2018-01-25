#include "taskmaster42.h"

void		print_general_status(const t_lst_proc *procs)
{
	int				running;
	int				finished;
	int				stopped;
	int				failed;
	int				total;
	const t_process	*proc;

	running = 0;
	finished = 0;
	stopped = 0;
	failed = 0;
	total = ft_lstlen(procs);
	for (; procs; LTONEXT(procs))
	{
		proc = LCONT(procs, t_process*);
		running += ISSTATE(proc, e_running);
		finished += ISSTATE(proc, e_completed);
		failed += ISSTATE(proc, e_critic);
		stopped += ISSTATE(proc, e_stopped);
	}
	ft_printf(
		"Running: %d, Completed: %d, Critic: %d, Stopped: %d, Total: %d\n",
		running, finished, failed, stopped, total);
}
