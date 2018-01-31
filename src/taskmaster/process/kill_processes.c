/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:02 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:02 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"
#include <signal.h>

void	kill_processes(int signum, const t_lst_proc *procs)
{
	t_lst_proc		*next;

	for (; procs; procs = next)
	{
		next = LNEXT(procs);
		kill_proc(signum, LCONT(procs, t_process*));
	}
}
