#include "taskmaster42.h"
#include <signal.h>

static void	reload_logger_(t_taskmast *taskmast, t_tskmst_logger *logger)
{
	if (!ft_strequ(taskmast->logger.log_file_path, logger->log_file_path))
	{
		ft_memdel((void**)&taskmast->logger.log_file_path);
		taskmast->logger.log_file_path = logger->log_file_path;
		logger->log_file_path = NULL;
		taskmast_setup_logger(taskmast);
	}
	taskmast->logger.log_to_term = logger->log_to_term;
}

void		reload_taskmast_config(
				t_taskmast *taskmast,
				const t_shvars *shvars,
				t_rostr file_path)
{
	t_taskmast	dummy_taskmast;

	ft_bzero(&dummy_taskmast, sizeof(dummy_taskmast));
	taskmast_load_all_config(shvars, &dummy_taskmast, file_path);

	reload_logger_(taskmast, &dummy_taskmast.logger);

	reload_procs_config(taskmast, dummy_taskmast.proc_cfgs);
	dummy_taskmast.proc_cfgs = NULL;
	dummy_taskmast.is_exiting = FALSE;
	del_taskmast(&dummy_taskmast);
}
