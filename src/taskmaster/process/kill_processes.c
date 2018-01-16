#include "taskmaster42.h"
#include <signal.h>

void	kill_processes(int signum, const t_lst_proc *procs)
{
	for (; procs; LTONEXT(procs))
		kill_proc(signum, LCONT(procs, t_process*));
}
