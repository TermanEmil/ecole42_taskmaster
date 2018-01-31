/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_has_to_be_restarted.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:10 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:10 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"
#include <sys/wait.h>

t_bool		proc_has_to_be_restarted(
				const t_process *proc,
				int waitpid_status,
				t_bool consider_restart_attempts)
{
	const int	*exit_codes;

	if (g_taskmast.is_exiting)
		return FALSE;
	if (proc->config->restart_mode == e_never)
		return FALSE;
	if (proc->config->restart_mode == e_unexpected_exit)
	{
		exit_codes = proc->config->expected_exit_statuss;	
		if (is_expected_exit_status(waitpid_status, exit_codes))
			return FALSE;
	}
	
	if (consider_restart_attempts)
		return proc->status.attempt < proc->config->restart_attempts;
	else
		return TRUE;
}
