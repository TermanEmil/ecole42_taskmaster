#include "taskmaster42.h"
#include <signal.h>

int			restart_process(t_process *proc)
{
	if (proc->status.state == e_stopped)
		kill_proc(SIGKILL, proc);

	close_process_open_fds(proc);
	proc->status.state = e_not_started;
	proc->status.waitpid_status = 0;
	proc->status.sig_on_kill = 0;
	ft_bzero(&proc->proc_time, sizeof(proc->proc_time));
	process_start(proc);
	return 0;
}
