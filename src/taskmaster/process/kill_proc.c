#include "taskmaster42.h"
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/*
** To recieve true log, I must save the log before calling kill.
*/

int		kill_proc(int signum, t_process *proc)
{
	char		buf[124];

	if (proc->pid <= 1)
		return -1;

	ft_bzero(buf, sizeof(buf));
	ft_sprintf(buf, "%s %s, PID: %d, uptime: %s\n\n",
		strsignal(signum), proc->name, proc->pid, proc_struptime(proc));

	TASKMAST_LOG("Sending signal to %s PID %d\n", proc->name, proc->pid);
	if (kill(proc->pid, signum) == -1)
	{
		if (errno != ESRCH)
		{
			TASKMAST_ERROR(FALSE, "kill(): pid = %d, signum = %d: %s",
				proc->pid, signum, strerror(errno));
			errno = 0;
			return -1;
		}
		errno = 0;
	}
	else
		TASKMAST_LOG(buf, "");
	return 0;
}
