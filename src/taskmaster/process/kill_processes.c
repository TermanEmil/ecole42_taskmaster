#include "taskmaster42.h"
#include <signal.h>

void	kill_processes(int signum, const t_lst_proc *procs)
{
	t_lst_proc	*next;

	for (; procs; procs = next)
	{
		next = LNEXT(procs);
		kill_proc(signum, LCONT(procs, t_process*));
	}
}
