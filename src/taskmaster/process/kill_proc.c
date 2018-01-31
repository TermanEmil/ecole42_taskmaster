/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:56 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:56 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

static void	save_log_str_(
				t_str buf,
				int signum,
				pid_t pid,
				t_rostr proc_name,
				t_rostr struptime)
{
	ft_sprintf(buf, "%s %s, PID: %d",
		strsignal(signum), proc_name, pid);

	if (struptime)
		ft_sprintf(buf + ft_strlen(buf), ", uptime: %s", struptime);

	ft_strcat(buf, "\n\n");
}

int		kill_proc(int signum, t_process *proc)
{
	return raw_proc_kill(signum, proc->pid, proc->name, proc_struptime(proc));
}

int		raw_proc_kill(
			int signum,
			pid_t pid,
			t_rostr proc_name,
			t_rostr struptime)
{
	char		buf[124];

	if (pid <= 1)
		return -1;

	ft_bzero(buf, sizeof(buf));
	save_log_str_(buf, signum, pid, proc_name, struptime);

	if (kill(pid, signum) == -1)
	{
		if (errno != ESRCH)
		{
			TASKMAST_ERROR(FALSE, "kill(): pid = %d, signum = %d: %s",
				pid, signum, strerror(errno));
			errno = 0;
			return -1;
		}
		errno = 0;
	}
	else
		TASKMAST_LOG(buf, "");
	return 0;
}
