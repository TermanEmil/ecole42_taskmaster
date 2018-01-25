#include "taskmaster42.h"

static int		pipe_strfd_(t_rostr str_fd, int *pipe_fd)
{
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (str_fd == NULL)
	{
		if (pipe(pipe_fd) != 0)
		{
			TASKMAST_ERROR(FALSE, "pipe: %s\n", strerror(errno));
			errno = 0;
			return -1;
		}
	}
	return 0;
}

/*
** Pipe the given process to the specified files or whatever in config.
*/

int				pipe_process(t_process *proc)
{
	int		ret;

	ret = 0;
	ret += pipe_strfd_(NULL, proc->stdin_fd);
	ret += pipe_strfd_(proc->config->stdout, proc->stdout_fd);
	ret += pipe_strfd_(proc->config->stderr, proc->stderr_fd);
	return (ret == 0) ? 0 : -1;
}
