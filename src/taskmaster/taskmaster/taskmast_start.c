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
	struct timespec	tm;

	tm.tv_sec = 0;
	tm.tv_nsec = 200;
	while (!g_taskmast.is_exiting)
	{
		g_taskmast.signal_flags.signals[SIGCHLD] = TRUE;
		taskmast_parse_signals();
		nanosleep(&tm, NULL);
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
	taskmast_setup_logger(taskmast);
	TASKMAST_LOG("Started Taskmaster, PID: %d\n", getpid());

	taskmast_reset_signals();
	init_waiter_thread_(&taskmast->waiter_thread);

	create_processes(taskmast, taskmast->proc_cfgs);
	ft_lstiter_mem(taskmast->procs, (void (*)(void*))&config_process_);
}
