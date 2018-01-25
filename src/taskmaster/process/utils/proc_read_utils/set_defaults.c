#include "config_reader_.h"

void			set_defaults(t_proc_config *proc_config)
{
	ft_bzero(proc_config, sizeof(*proc_config));
	proc_config->nb_of_procs = 1;
	proc_config->autostart = TRUE;
	proc_config->restart_attempts = 0;
	proc_config->sig_graceful_stop = SIGINT;
	proc_config->umask = DEFAULT_UMASK;
	proc_config->restart_attempts = 1;
	proc_config->restart_mode = e_never;
	proc_config->time_before_forced_kill = 1;
	proc_config->success_time = -1;
}
