/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:59 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:59 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"
#include <signal.h>

int			restart_process(t_process *proc)
{
	if (ISSTATE(proc, e_grace_stopping))
		return -1;

	TASKMAST_LOG("%s PID: %d restarting\n", proc->name, proc->pid);
	if (ISSTATE(proc, e_stopped))
	{
		TASKMAST_ERROR(FALSE, "%s: can't restart stopped processes.\n",
			proc->name);
		return -1;
	}
	
	if (ISSTATE(proc, e_running))
	{
		proc_graceful_stop(proc);
		proc->status.state = e_completed;
	}

	close_process_open_fds(proc);
	proc->status.state = e_not_started;
	proc->status.waitpid_status = 0;
	proc->status.sig_on_kill = 0;
	ft_bzero(&proc->proc_time, sizeof(proc->proc_time));
	process_start(proc);
	return 0;
}
