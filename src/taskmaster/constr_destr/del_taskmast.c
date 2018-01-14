#include "taskmaster42.h"
#include "taskmaster42_utils_.h"

void	del_taskmast(t_taskmast *taskmast)
{
	taskmast->thread_should_die = TRUE;
	pthread_join(taskmast->waiter_thread, NULL);
	taskmast_log("Quit\n");
	ft_lstdel(&taskmast->procs, (t_ldel_func*)&del_proc);
	ft_lstdel(&taskmast->proc_cfgs, (t_ldel_func*)&del_proc_config);
	ft_memdel((void**)&taskmast->logger.log_file_path);
	close_if_open(&taskmast->logger.log_file_fd);
}
