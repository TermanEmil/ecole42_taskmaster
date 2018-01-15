#include "taskmaster42.h"
#include "taskmaster42_utils_.h"
#include <fcntl.h>

#define WR_CR_TR_ O_WRONLY | O_CREAT | O_TRUNC

static void	create_processes_(t_taskmast *taskmast)
{
	t_lst_proccfg	*proc_cfgs;
	t_proc_config	*config;
	t_process		proc;
	int				i;

	for (proc_cfgs = taskmast->proc_cfgs; proc_cfgs; LTONEXT(proc_cfgs))
	{
		config = LCONT(proc_cfgs, t_proc_config*);
		for (i = 0; i < config->nb_of_procs; i++)
		{
			proc = new_process(config, taskmast->procs);
			ft_lstadd(&taskmast->procs, ft_lstnew(&proc, sizeof(proc)));
			TASKMAST_LOG("Process %s created\n", proc.name);
		}
	}
}

static void	config_process_(t_process *proc)
{
	if (proc->config->autostart)
		process_start(proc);
}

void	taskmast_start(t_taskmast *taskmast)
{
	int		fd;

	close_if_open(&taskmast->logger.log_file_fd);
	if (taskmast->logger.log_file_path)
	{
		fd = open(taskmast->logger.log_file_path, WR_CR_TR_, 0644);
		if (fd == -1)
		{
			TASKMAST_ERROR(FALSE, "%s: %s\n",
				taskmast->logger.log_file_path, strerror(errno));
			errno = 0;
		}
		else
			taskmast->logger.log_file_fd = fd;
	}
	TASKMAST_LOG("Started Taskmaster, PID: %d\n", getpid());
	create_processes_(taskmast);
	ft_lstiter_mem(taskmast->procs, (void (*)(void*))&config_process_);
}
