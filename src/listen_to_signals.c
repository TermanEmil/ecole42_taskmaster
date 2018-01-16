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
	TASKMAST_LOG("SIGINT\n", "");
	g_shinput->signaled_sigint = TRUE;
}

static void	handle_sigchld_(int signum)
{
	pid_t	pid;
	int		status;

	while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		if (!g_taskmast.is_exiting)
			parse_process_waitpid(pid, status);
	}
	if (pid == -1 && errno != ECHILD)
		TASKMAST_ERROR(FALSE, "waitpid(): %s\n", strerror(errno));
	errno = 0;
	update_alarm();
}

static void	handle_sigalarm(int signum)
{
	(void)signum;
	if (g_taskmast.next_alarm == NULL)
		return;
	if (kill(g_taskmast.next_alarm->pid, SIGKILL) == -1)
	{
		TASKMAST_ERROR(FALSE, "handle_alarm(): kill(): %s\n", strerror(errno));
		errno = 0;
	}
	else
	{
		taskmast_log_kill_exceed_time(g_taskmast.next_alarm);
		g_taskmast.next_alarm = NULL;
	}
	update_alarm();
}

void		listen_to_signals(void)
{
	ft_sigaction(SIGINT, &handle_sigint);
	signal(SIGCHLD, &handle_sigchld_);
	signal(SIGALRM, &handle_sigalarm);
}
