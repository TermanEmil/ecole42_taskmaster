#include "process42.h"

void		discard_proc_redirs(t_process *proc)
{
	proc->stdin_fd[0] = -1;
	proc->stdin_fd[1] = -1;
	proc->stdout_fd[0] = -1;
	proc->stdout_fd[1] = -1;
	proc->stderr_fd[0] = -1;
	proc->stderr_fd[1] = -1;
}
