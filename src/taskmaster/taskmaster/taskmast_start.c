#include "taskmaster42.h"
#include <fcntl.h>
#include <time.h>

static void	config_process_(t_process *proc)
{
	if (proc->config->autostart)
		process_start(proc);
}

static void	*waiter_thread_func_(void *varg)
{
	while (!g_taskmast.is_exiting)
	{
		taskmast_parse_signals();
		usleep(CHECK_SIG_FLAGS_INTERVAL);
		errno = 0;
	}
	return NULL;
}

static void	init_waiter_thread_(pthread_t *tid)
{
	if (pthread_create(tid, NULL, &waiter_thread_func_, NULL) != 0)
		TASKMAST_ERROR(TRUE, "pthread_create(): %s\n", strerror(errno));
}

void		taskmast_start(t_taskmast *taskmast)
{
	taskmast->signal_flags.its_safe = FALSE;
	taskmast_setup_logger(taskmast);
	TASKMAST_LOG("Started Taskmaster, PID: %d\n", getpid());

	create_processes(taskmast, taskmast->proc_cfgs);
	ft_lstiter_mem(taskmast->procs, (void (*)(void*))&config_process_);
	init_waiter_thread_(&taskmast->waiter_thread);

	taskmast->signal_flags.its_safe = TRUE;
}
