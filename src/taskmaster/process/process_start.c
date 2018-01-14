#include "taskmaster42.h"
#include "taskmaster42_utils_.h"
#include "shell42.h"

#include <wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

static int		process_piping_(t_rostr std_fd_val, int *pipe_fd)
{
	int		fd;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (std_fd_val == NULL)
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

int		process_start(t_process *process)
{
	t_proc_config	*config;


	config = process->config;
	if (config->launch_cmd == NULL || config->prog_name == NULL)
		return -1;
	
	if (access(config->launch_cmd, X_OK) != 0)
	{
		TASKMAST_ERROR(FALSE, "%s: %s\n", config->launch_cmd, strerror(errno));
		errno = 0;
		return -1;
	}

	process_piping_(NULL, process->stdin_fd);
	process_piping_(config->stdout, process->stdout_fd);
	process_piping_(config->stderr, process->stderr_fd);

	if ((process->pid = fork()) == -1)
	{
		TASKMAST_ERROR(FALSE, "Failed to fork() for %s: %s\n",
			process->config->prog_name, strerror(errno));
		errno = 0;
		close_process_open_fds(process);
		return -1;
	}

	if (process->pid == 0)
	{
		t_str	*env_tab;

		close_if_open(&process->stdin_fd[1]);
		close_if_open(&process->stdout_fd[0]);
		close_if_open(&process->stderr_fd[0]);
		dup2_close(process->stdout_fd[0], STDIN_FILENO);
		dup2_close(process->stdout_fd[1], STDOUT_FILENO);
		dup2_close(process->stderr_fd[1], STDERR_FILENO);
		process_std_redir_to_file(config->stdout, STDOUT_FILENO);
		process_std_redir_to_file(config->stderr, STDERR_FILENO);

		if (config->environment)
			env_tab = config->environment;
		else
			env_tab = shvars_form_key_val_tab(g_shdata.shvars.env);
		run_command(config->launch_cmd, env_tab);
	}
	else
	{
		close_if_open(&process->stdin_fd[0]);
		close_if_open(&process->stdin_fd[1]);
		close_if_open(&process->stdout_fd[1]);
		close_if_open(&process->stderr_fd[1]);

		close_if_open(&process->stdout_fd[0]);
		close_if_open(&process->stderr_fd[0]);

		process->status.started = TRUE;
		process->proc_time.start_time = time(NULL);
		TASKMAST_LOG("Started %s PID: %d\n", process->name, process->pid);
	}
	return 0;
}
