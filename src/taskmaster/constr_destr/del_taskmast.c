#include "taskmaster42.h"
#include "taskmaster42_utils_.h"
#include <signal.h>

static void	force_kill_no_restart_all_procs_(t_taskmast *taskmast)
{
	if (taskmast->is_exiting)
		TASKMAST_LOG("Killing all childprocesses\n", "");
	taskmast->is_exiting = TRUE;
	kill_processes(SIGKILL, taskmast->procs);
}

void		del_taskmast(t_taskmast *taskmast)
{
	if (taskmast->is_exiting)
		TASKMAST_LOG("Freeing Taskmaster resources\n", "");
	force_kill_no_restart_all_procs_(taskmast);	

	ft_lstdel(&taskmast->procs, (t_ldel_func*)&del_proc);
	ft_lstdel(&taskmast->proc_cfgs, (t_ldel_func*)&del_proc_config);
	ft_memdel((void**)&taskmast->logger.log_file_path);
	close_if_open(&taskmast->logger.log_file_fd);
	ft_lstdel(&taskmast->schedules, &std_mem_del);
}
