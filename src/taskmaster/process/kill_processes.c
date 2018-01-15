#include "taskmaster42.h"
#include <signal.h>

void	kill_processes(int signum, const t_lst_proc *procs)
{
	const t_process	*proc;

	for (; procs; LTONEXT(procs))
	{
		proc = LCONT(procs, t_process*);
		if (kill(proc->pid, signum) == -1)
		{
			if (errno != ESRCH)
			{
				TASKMAST_ERROR(FALSE, "kill(): pid = %d, signum = %d: %s",
					proc->pid, signum, strerror(errno));
			}
			errno = 0;
		}
		else
		{
			TASKMAST_LOG("Killed %s, PID: %d, uptime: %s\n",
				proc->name, proc->pid, proc_struptime(proc));
		}
	}
}
