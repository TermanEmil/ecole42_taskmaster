#include "taskmaster42.h"

void	del_proc_config(t_proc_config *proc_config)
{
	ft_memdel((void**)&proc_config->prog_name);
	ft_memdel((void**)&proc_config->launch_cmd);
	ft_memdel((void**)&proc_config->expected_exit_codes);
	ft_memdel((void**)&proc_config->stdout);
	ft_memdel((void**)&proc_config->stderr);
	ft_memdel((void**)&proc_config->dir);
	if (proc_config->environment)
		ft_free_bidimens(proc_config->environment);
	free(proc_config);
}
