#include "taskmaster42.h"
#include <fcntl.h>

static void	config_process_(t_process *proc)
{
	if (proc->config->autostart)
		process_start(proc);
}

void	taskmast_start(t_taskmast *taskmast)
{
	taskmast_setup_logger(taskmast);
	TASKMAST_LOG("Started Taskmaster, PID: %d\n", getpid());

	taskmast_reset_signals();

	create_processes(taskmast, taskmast->proc_cfgs);
	ft_lstiter_mem(taskmast->procs, (void (*)(void*))&config_process_);
}
