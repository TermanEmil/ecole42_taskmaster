#include "taskmaster42.h"
#include <limits.h>

static int	fork_fail_(t_process *proc)
{
	TASKMAST_ERROR(FALSE, "Failed to fork() for %s: %s\n",
			proc->config->prog_name, strerror(errno));
	errno = 0;
	close_process_open_fds(proc);
	return -1;
}

static int	parse_launch_cmd_(t_process *proc)
{
	t_proc_config	*config;

	config = proc->config;
	if (config->launch_cmd == NULL || ft_strequ(config->launch_cmd, ""))
	{
		TASKMAST_ERROR(FALSE, "%s: No launch_cmd is specified\n",
			config->prog_name);
		return -1;
	}
	return 0;
}

int		process_start(t_process *process)
{
	if (parse_launch_cmd_(process) != 0)
		return -1;

	pipe_process(process);
	process->pid = fork();

	if (process->pid == -1)
		return fork_fail_(process);
	else if (process->pid == 0)
		child_process_start(process);
	else
		father_process_start(process);
	return 0;
}
