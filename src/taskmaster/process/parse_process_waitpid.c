#include "process42.h"
#include "taskmaster42.h"
#include <signal.h>
#include <wait.h>
#include <string.h>

void		process_normal_exit(t_process *proc, int status)
{
	TASKMAST_LOG("%s, pid: %d exited. Exitcode: `%d', uptime: %s\n",
		proc->name, proc->pid, WEXITSTATUS(status), proc_struptime(proc));

	proc->proc_time.running_time = proc_uptime(proc);
	proc->proc_time.finish_time = time(NULL);
	proc->status.waitpid_status = status;
	proc->status.state = e_completed;
	update_proc_state(proc);

	if (proc_has_to_be_restarted(proc, status, TRUE))
		restart_process(proc);
}

void		process_signal_exit(t_process *proc, int status)
{
	TASKMAST_LOG("%s, pid: %d signal exited. Signal `%s', uptime: %s\n",
		proc->name, proc->pid, strsignal(WTERMSIG(status)),
		proc_struptime(proc));

	proc->proc_time.running_time = proc_uptime(proc);
	proc->proc_time.finish_time = time(NULL);
	proc->status.waitpid_status = status;
	proc->status.sig_on_kill = WTERMSIG(status);
	proc->status.state = e_completed;
	update_proc_state(proc);
	
	if (proc_has_to_be_restarted(proc, status, TRUE))
		restart_process(proc);
}

void		process_stopped(t_process *proc, int status)
{
	TASKMAST_LOG("Process %s, pid: %d stopped with the signal %d\n",
		proc->name, proc->pid, WSTOPSIG(status));
}

void		process_continue(t_process *proc, int status)
{
	TASKMAST_LOG("Process %s, pid: %d continued\n", proc->name, proc->pid);
}

void		parse_process_waitpid(pid_t waited_pid, int wait_status)
{
	t_process	*proc;

	if ((proc = lst_process_pidof(g_taskmast.procs, waited_pid)) == NULL)
		return;

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
