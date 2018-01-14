#include "taskmaster42.h"
#include "shell42.h"

static void	init_taskmast_events_()
{
	event_global_force_add("memory_frees_free_taskmaster",
		event_inst_new((t_handler_f*)&del_taskmast, &g_taskmast));
}

void		init_taskmaster(t_rostr config_file)
{
	taskmast_load_all_config(&g_shdata.shvars, &g_taskmast, config_file);
	init_taskmast_events_();
	g_taskmast.logger.log_is_on = TRUE;	
	g_taskmast.logger.log_to_term = TRUE;
}
