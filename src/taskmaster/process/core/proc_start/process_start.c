#include "taskmaster42.h"
#include "taskmaster42_utils_.h"
#include "shell42.h"

#include <fcntl.h>
#include <time.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int		process_start(t_process *process)
{
	t_proc_config	*config;

	config = process->config;
	if (config->launch_cmd == NULL || ft_strequ(config->launch_cmd, ""))
	{
		TASKMAST_ERROR(FALSE, "No launch_cmd is specified\n", "");
		return -1;
	}

	pipe_process(process);
	process->pid = fork();

	if (process->pid == -1)
	{
		TASKMAST_ERROR(FALSE, "Failed to fork() for %s: %s\n",
			process->config->prog_name, strerror(errno));
		errno = 0;
		close_process_open_fds(process);
		return -1;
	}

	if (process->pid == 0)
		child_process_start(process);
	else
		father_process_start(process);
	return 0;
}
