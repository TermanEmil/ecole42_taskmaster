#include "taskmaster42.h"
#include <wait.h>

#define SIG_FLGS_ (g_taskmast.signal_flags)

static void		parse_sigchld_()
{
	pid_t	pid;
	int		status;

	if (!SIG_FLGS_.signals[SIGCLD] || !SIG_FLGS_.its_safe)
		return;
	
	SIG_FLGS_.its_safe = FALSE;
	SIG_FLGS_.signals[SIGCLD] = FALSE;

	while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
	{
		if (!g_taskmast.is_exiting)
			parse_process_waitpid(pid, status);
	}
	if (pid == -1 && errno != ECHILD)
		TASKMAST_ERROR(FALSE, "waitpid(): %s\n", strerror(errno));
	errno = 0;
	update_alarm();

	SIG_FLGS_.its_safe = TRUE;
	taskmast_parse_signals();
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
	taskmast_parse_signals();
}

static void		parse_sighup_()
{
	if (!SIG_FLGS_.signals[SIGHUP] || !SIG_FLGS_.its_safe)
		return;

	SIG_FLGS_.its_safe = FALSE;
	SIG_FLGS_.signals[SIGHUP] = FALSE;

	term_restore_to_old_term_data();
	TASKMAST_LOG("Reloading Config File\n", "");
	reload_taskmast_config(&g_taskmast, &g_shdata.shvars, g_taskmast.cfg_path);
	term_enable_raw_mode(term_get_data());
	update_alarm();

	SIG_FLGS_.its_safe = TRUE;
	taskmast_parse_signals();
}

void			taskmast_parse_signals()
{
	if (!SIG_FLGS_.its_safe)
		return;

	if (SIG_FLGS_.signals[SIGCHLD])
		parse_sigchld_();
	if (SIG_FLGS_.signals[SIGALRM])
		parse_sigalarm_();
	if (SIG_FLGS_.signals[SIGHUP])
		parse_sighup_();
	taskmast_reset_signals();
}
