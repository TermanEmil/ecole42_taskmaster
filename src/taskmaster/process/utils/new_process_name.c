#include "taskmaster42.h"

t_str	new_process_name(const t_process *proc)
{
	char	buf[16];

	ft_bufitoa(proc->name_id, buf);
	return ft_strmegajoin(3, proc->config->prog_name, "_", buf);
}
