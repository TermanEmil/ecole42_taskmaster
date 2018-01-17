#include "taskmaster42.h"
#include <signal.h>

int			restart_process(t_process *proc)
{
	TASKMAST_LOG("%s PID: %d restarting\n", proc->name, proc->pid);
	if (ISSTATE(proc, e_stopped) || ISSTATE(proc, e_running))
	{
		kill_proc(SIGKILL, proc);
		proc->status.state = e_completed;
	}

	close_process_open_fds(proc);
	proc->status.state = e_not_started;
	proc->status.waitpid_status = 0;
	proc->status.sig_on_kill = 0;
	ft_bzero(&proc->proc_time, sizeof(proc->proc_time));
	process_start(proc);
	return 0;
}
