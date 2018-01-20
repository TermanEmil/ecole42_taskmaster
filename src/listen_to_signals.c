/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_to_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 16:57:33 by eterman           #+#    #+#             */
/*   Updated: 2017/05/15 11:01:57 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <signal.h>
#include <wait.h>
#include <string.h>
#include "shell42.h"
#include "eventlib.h"
#include "ft_signals.h"
#include "taskmaster42.h"

static void	handle_sigint(int signum)
{
	(void)signum;
	g_shinput->signaled_sigint = TRUE;
}

static void	handle_sigchld_(int signum)
{
	pid_t	pid;
	int		status;

	while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
	{
		if (!g_taskmast.is_exiting)
			parse_process_waitpid(pid, status);
	}
	if (pid == -1 && errno != ECHILD)
		TASKMAST_ERROR(FALSE, "waitpid(): %s\n", strerror(errno));
	errno = 0;
	update_alarm();
	signal(SIGCHLD, &handle_sigchld_);
}

static void	handle_sigalarm(int signum)
{
	g_taskmast.next_schedl = NULL;
	update_alarm();
	signal(SIGALRM, &handle_sigalarm);
}

static void	handle_sighub_(int signum)
{
	(void)signum;
	term_restore_to_old_term_data();
	TASKMAST_LOG("Reloading Config File\n", "");
	reload_taskmast_config(&g_taskmast, &g_shdata.shvars, g_taskmast.cfg_path);
	term_enable_raw_mode(term_get_data());
	update_alarm();
	signal(SIGHUP, &handle_sighub_);
}

void		listen_to_signals(void)
{
	ft_sigaction(SIGINT, &handle_sigint);
	signal(SIGCHLD, &handle_sigchld_);
	signal(SIGALRM, &handle_sigalarm);
	signal(SIGHUP, &handle_sighub_);
}
