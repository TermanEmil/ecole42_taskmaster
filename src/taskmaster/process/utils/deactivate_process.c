#include "taskmaster42.h"

void			deactivate_process(t_process *proc)
{
	proc->active = FALSE;
}
