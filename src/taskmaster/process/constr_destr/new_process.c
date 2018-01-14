#include "process42.h"

t_process	new_process(t_proc_config *config, const t_lst_proc *processes)
{
	t_process	process;

	ft_bzero(&process, sizeof(process));
	process.status.started = FALSE;
	process.config = config;
	process.name_id = get_process_name_id(&process, processes);
	process.name = new_process_name(&process);
	return process;
}
