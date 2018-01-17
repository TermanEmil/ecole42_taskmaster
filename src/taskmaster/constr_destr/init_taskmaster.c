#include "taskmaster42.h"
#include "shell42.h"

static void	init_taskmast_events_()
{
	event_global_force_add("memory_frees_free_taskmaster",
		event_inst_new((t_handler_f*)&del_taskmast, &g_taskmast));
}

void		init_taskmaster(t_rostr config_file)
{
	int		ret;

	taskmast_load_all_config(&g_shdata.shvars, &g_taskmast, config_file);
	init_taskmast_events_();
	g_taskmast.logger.log_is_on = TRUE;	
	g_taskmast.logger.log_to_term = TRUE;
	g_taskmast.cfg_path = config_file;
	
	// ret = pthread_create(&g_taskmast.thread.waiter_thread, NULL,
	// 	continous_update_processes_stats, NULL);
	// if (ret != 0)
	// 	TASKMAST_ERROR(TRUE, "pthread_create(): %s\n", strerror(errno));
	// if (pthread_cond_init(&g_taskmast.thread.cv, NULL) != 0)
	// 	TASKMAST_ERROR(TRUE, "pthread_cond_init(): %s\n", strerror(errno));
	// if (pthread_mutex_init(&g_taskmast.thread.lock, NULL) != 0)
	// 	TASKMAST_ERROR(TRUE, "pthread_mutex_init(): %s\n", strerror(errno));
}
