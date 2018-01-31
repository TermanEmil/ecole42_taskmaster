/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigkill_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:50 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:50 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"
#include <signal.h>

void		sigkill_pid(t_taskmast *taskmaster, pid_t pid)
{
	t_process	*proc;

	if (pid <= 1)
		return;

	proc = lst_process_pidof(taskmaster->procs, pid);
	if (proc)
	{
		kill_proc(SIGKILL, proc);
	}
}
