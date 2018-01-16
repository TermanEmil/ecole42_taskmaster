#include "process42.h"

static void	init_redir_fds_(t_process *proc)
{
	proc->stdin_fd[0] = -1;
	proc->stdout_fd[0] = -1;
	proc->stderr_fd[0] = -1;

	proc->stdin_fd[1] = -1;
	proc->stdout_fd[1] = -1;
	proc->stderr_fd[1] = -1;
}

t_process	new_process(t_proc_config *config, const t_lst_proc *processes)
{
	t_process	process;

	ft_bzero(&process, sizeof(process));
	init_redir_fds_(&process);
	process.pid = -1;
	process.status.state = e_not_started;
	process.config = config;
	process.name_id = get_process_name_id(&process, processes);
	process.name = new_process_name(&process);
	return process;
}
