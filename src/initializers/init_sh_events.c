#include "shell42.h"

void	init_sh_events(void)
{
	event_global_force_add("memory_frees", event_inst_new(
		(t_handler_f*)&shdata_destruct, &g_shdata));
	
	if (g_shdata.is_term)
	{
		event_global_force_add("at_exit_restore_term", event_inst_new(
			(t_handler_f*)&term_restore, &term_get_data()->old_term));
	}
}
