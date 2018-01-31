/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_proc_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:02 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:02 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process42.h"
#include <signal.h>
#include <sys/wait.h>

void		update_proc_state(t_process *proc)
{
	int		wait_status;

	wait_status = proc->status.waitpid_status;
	if (WIFSIGNALED(wait_status) && WTERMSIG(wait_status) == SIGSTOP)
		proc->status.state = e_stopped;
	else if (proc_has_to_be_restarted(proc, wait_status, FALSE))
	{
		if (proc->status.attempt >= proc->config->restart_attempts)
			proc->status.state = e_critic;
	}
}
