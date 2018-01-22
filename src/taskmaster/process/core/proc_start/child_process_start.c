#include "taskmaster42.h"
#include "taskmaster42_utils_.h"
#include <sys/stat.h>

#define EXIT_CMD_NOT_FOUND_ 127

static void	ignore_ctrl_c_()
{
	if (setsid() == -1)
		TASKMAST_ERROR(FALSE, "setsid(): %s\n", strerror(errno));
	errno = 0;
}

static void	parse_redirs_(t_process *proc)
{
	close_if_open(&proc->stdin_fd[1]);
	close_if_open(&proc->stdout_fd[0]);
	close_if_open(&proc->stderr_fd[0]);
	dup2_close(proc->stdin_fd[0], STDIN_FILENO);
	dup2_close(proc->stdout_fd[1], STDOUT_FILENO);
	dup2_close(proc->stderr_fd[1], STDERR_FILENO);
	process_std_redir_to_file(proc->config->stdout, STDOUT_FILENO);
	process_std_redir_to_file(proc->config->stderr, STDERR_FILENO);
}

static int	proc_mv_to_dir(t_rostr dir)
{
	if (dir)
		if (chdir(dir) == -1)
		{
			TASKMAST_ERROR(FALSE, "%s: %s.\n", dir, strerror(errno));
			return -1;
		}
	return 0;
}

void		child_process_start(t_process *proc)
{
	t_str	*env_tab;

	ignore_ctrl_c_();
	parse_redirs_(proc);
	umask(proc->config->umask);

	if (proc_mv_to_dir(proc->config->dir) == -1)
		_exit(EXIT_FAILURE);

	if (proc->config->environment)
		env_tab = proc->config->environment;
	else
		env_tab = shvars_form_key_val_tab(g_shdata.shvars.env);

	run_command(proc->config->launch_cmd, env_tab);
	_exit(EXIT_CMD_NOT_FOUND_);
}
