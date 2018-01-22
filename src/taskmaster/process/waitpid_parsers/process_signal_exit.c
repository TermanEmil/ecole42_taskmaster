#include "taskmaster42.h"
#include <wait.h>
#include <string.h>

static void	update_proc_stats_(t_process *proc, int waitpid_status)
{
	proc->proc_time.running_time = proc_uptime(proc);
	proc->proc_time.finish_time = time(NULL);
	proc->status.waitpid_status = waitpid_status;
	proc->status.sig_on_kill = WTERMSIG(waitpid_status);
	proc->status.state = e_completed;
}

void		process_signal_exit(t_process *proc, int status)
{
	TASKMAST_LOG("%s, pid: %d signaled. Signal `%s', uptime: %s.\n",
		proc->name, proc->pid, strsignal(WTERMSIG(status)),
		proc_struptime(proc));

	if (ISSTATE(proc, e_grace_stopping))
	{
		deactivate_process(proc);
		return;
	}

	update_proc_stats_(proc, status);
	update_proc_state(proc);
	
	if (proc_has_to_be_restarted(proc, status, TRUE))
		restart_process(proc);
}
