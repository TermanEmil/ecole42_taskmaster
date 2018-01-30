#include "taskmaster42.h"
#include "shell42.h"
#include <unistd.h>

static void	really_delete_taskmst_(t_taskmast *taskmast)
{
	taskmast->is_exiting = TRUE;
	del_taskmast(taskmast);
}

static void	init_taskmast_events_()
{
	event_global_force_add("memory_frees_free_taskmaster",
		event_inst_new((t_handler_f*)&really_delete_taskmst_, &g_taskmast));
}

void		init_taskmaster(t_rostr config_file)
{
	char	buf[16];

	ft_bzero(&g_taskmast, sizeof(g_taskmast));
	taskmast_load_all_config(&g_shdata.shvars, &g_taskmast, config_file);
	init_taskmast_events_();
	g_taskmast.logger.log_is_on = TRUE;	
	g_taskmast.cfg_path = config_file;

	htab_set_pair(g_shdata.shvars.env, new_hashpair(
		new_hashmem_str("MyPid"),
		new_hashmem_str(ft_bufitoa(getpid(), buf))));
}
