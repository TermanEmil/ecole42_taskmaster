#include "taskmaster42.h"

void	del_proc(t_process *proc)
{
	close_process_open_fds(proc);
	ft_memdel((void**)&proc->name);
	free(proc);	
}
