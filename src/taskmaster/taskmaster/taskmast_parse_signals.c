#include "taskmaster42.h"
#include <sys/wait.h>

#define SIG_FLGS_ g_taskmast.signal_flags

static void		parse_sigchld_()
{
	pid_t	pid;
	int		status;

	if (!SIG_FLGS_.its_safe)
		return;
	
	SIG_FLGS_.its_safe = FALSE;
	SIG_FLGS_.signals[SIGCHLD] = FALSE;

	while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
		parse_process_waitpid(pid, status);
	if (pid == -1 && errno != 0 && errno != ECHILD)
		TASKMAST_ERROR(FALSE, "waitpid(): %s\n", strerror(errno));
	errno = 0;
	update_alarm();

	SIG_FLGS_.its_safe = TRUE;
}

static void		parse_sigalarm_()
{
	if (!SIG_FLGS_.signals[SIGALRM] || !SIG_FLGS_.its_safe)
		return;

	SIG_FLGS_.its_safe = FALSE;
	SIG_FLGS_.signals[SIGALRM] = FALSE;

	g_taskmast.next_schedl = NULL;
	update_alarm();

	SIG_FLGS_.its_safe = TRUE;
}

static void		parse_sighup_()
{
	if (!SIG_FLGS_.signals[SIGHUP] || !SIG_FLGS_.its_safe)
		return;

	SIG_FLGS_.its_safe = FALSE;
	SIG_FLGS_.signals[SIGHUP] = FALSE;

	TASKMAST_PRINT(sync_printf(&g_printf_mutex,
		STDOUT_FILENO, "Reloading Config File\n"));
	taskmast_log("Reloading Config File\n", "");
	reload_taskmast_config(&g_taskmast, &g_shdata.shvars, g_taskmast.cfg_path);
	update_alarm();

	SIG_FLGS_.its_safe = TRUE;
}

void			taskmast_parse_signals()
{
	if (!SIG_FLGS_.its_safe)
		return;

	// if (SIG_FLGS_.signals[SIGCHLD])
	parse_sigchld_();
	if (SIG_FLGS_.signals[SIGALRM])
		parse_sigalarm_();
	if (SIG_FLGS_.signals[SIGHUP])
		parse_sighup_();
}
