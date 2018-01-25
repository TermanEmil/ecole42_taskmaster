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
#include <sys/wait.h>
#include <string.h>
#include "shell42.h"
#include "eventlib.h"
#include "ft_signals.h"
#include "taskmaster42.h"

static void	ft_signal_(int signum, void (*handler)(int))
{
	if (signal(signum, handler) == SIG_ERR)
		TASKMAST_ERROR(TRUE, "signal(): %s\n", strerror(errno));
}

static void	handle_sigint(int signum)
{
	(void)signum;
	g_shinput->signaled_sigint = TRUE;
}

static void	set_tskmast_signal(int signum)
{
	g_taskmast.signal_flags.signals[signum] = TRUE;
	if (g_taskmast.signal_flags.its_safe)
		taskmast_parse_signals();
}

void		listen_to_signals(void)
{
	ft_sigaction(SIGINT, &handle_sigint);
	ft_signal_(SIGCHLD, &set_tskmast_signal);
	ft_signal_(SIGALRM, &set_tskmast_signal);
	ft_signal_(SIGHUP, &set_tskmast_signal);
}
