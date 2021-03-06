/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:58 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:58 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"
#include <signal.h>

int		stop_process(t_process *proc)
{
	if (!ISSTATE(proc, e_running))
	{
		TASKMAST_ERROR(FALSE, "%s must be running to stop it.\n",
			proc->name);
		return -1;
	}
	TASKMAST_LOG("Stopping %s PID: %d.\n", proc->name, proc->pid);
	if (kill_proc(SIGSTOP, proc) != 0)
	{
		TASKMAST_ERROR(FALSE, "%s: Failed to stop.\n", proc->name);
		return -1;
	}
	return 0;
}
