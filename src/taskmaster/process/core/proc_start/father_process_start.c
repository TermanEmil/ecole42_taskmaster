#include "taskmaster42.h"
#include "taskmaster42_utils_.h"

static void	set_proc_stats_(t_process *proc)
{
	proc->status.state = e_running;
	proc->proc_time.start_time = time(NULL);
	proc->proc_time.finish_time = -1;
	proc->proc_time.running_time = 0;
	proc->status.attempt++;
}

void		father_process_start(t_process *proc)
{
	close_if_open(&proc->stdin_fd[0]);
	close_if_open(&proc->stdout_fd[1]);
	close_if_open(&proc->stderr_fd[1]);

	set_proc_stats_(proc);
	update_alarm();

	TASKMAST_LOG("Started %s PID: %d\n", proc->name, proc->pid);
}
