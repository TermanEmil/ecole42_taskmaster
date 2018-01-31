/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process_waitpid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:00 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:00 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"
#include <sys/wait.h>

void		parse_process_waitpid(pid_t waited_pid, int wait_status)
{
	t_process	*proc;

	proc = lst_process_pidof(g_taskmast.procs, waited_pid);
	if (proc == NULL)
	{
		TASKMAST_ERROR(FALSE, "parse waitpid: PID: %d: no such process\n",
			waited_pid);
		return;
	}

	if (WIFEXITED(wait_status))
		process_normal_exit(proc, wait_status);
	else if (WIFSIGNALED(wait_status))
		process_signal_exit(proc, wait_status);
	else if (WIFSTOPPED(wait_status))
		process_stopped(proc, wait_status);
	else if (WIFCONTINUED(wait_status))
		process_continue(proc, wait_status);
	else
		TASKMAST_ERROR(FALSE, "Invalid waitpid() status: %d\n", wait_status);
}
