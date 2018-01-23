#include "taskmaster42.h"

void	del_proc(t_process *proc)
{
	close_process_open_fds(proc);
	if (proc->config)
		del_proc_config(proc->config);
	ft_memdel((void**)&proc->name);
	free(proc);	
}
