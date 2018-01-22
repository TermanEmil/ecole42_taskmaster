#include "taskmaster42.h"
#include <wait.h>

void		parse_process_waitpid(pid_t waited_pid, int wait_status)
{
	t_process	*proc;

	proc = lst_process_pidof(g_taskmast.procs, waited_pid);
	if (proc == NULL)
	{
		TASKMAST_LOG("PID: %d: no such process\n", waited_pid);
		return;
	}

	if (WIFEXITED(wait_status))
		process_normal_exit(proc, wait_status);
	else if (WIFSIGNALED(wait_status))
		process_signal_exit(proc, wait_status);
	else if (WIFSTOPPED(wait_status))
		process_stopped(proc, wait_status);
	else if (WIFCONTINUED(wait_status))
		process_continue(proc, wait_status);
	else
		TASKMAST_ERROR(FALSE, "Invalid waitpid() status: %d\n", wait_status);
}
