/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:57 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:57 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"
#include <signal.h>

int			continue_process(t_process *proc)
{
	if (!ISSTATE(proc, e_stopped))
	{
		TASKMAST_ERROR(FALSE, "%s must be stopped to continue it.\n",
			proc->name);
		return -1;
	}
	TASKMAST_LOG("Continuing %s PID: %d.\n", proc->name, proc->pid);
	if (kill_proc(SIGCONT, proc) != 0)
	{
		TASKMAST_ERROR(FALSE, "%s: Failed to continue.\n", proc->name);
		return -1;
	}
	return 0;
}
