/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_continue.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:00 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:00 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"
#include <time.h>

void		process_continue(t_process *proc, int status)
{
	TASKMAST_LOG("Process %s, pid: %d continued.\n", proc->name, proc->pid);
	if (ISSTATE(proc, e_grace_stopping))
		return;
	proc->status.waitpid_status = status;
	proc->proc_time.start_time = time(NULL);
	proc->status.state = e_running;
}
