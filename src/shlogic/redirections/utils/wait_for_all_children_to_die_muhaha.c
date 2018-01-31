/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_all_children_to_die_muhaha.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:20 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:20 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_redirs_.h"
#include "taskmaster42.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
** It's ok if it didn't wait for anything.
*/

void	wait_for_all_children_to_die_muhaha()
{
	pid_t		*pid;
	t_lst_int	*started_procs;

	started_procs = g_shdata.started_procs;
	for (; started_procs; LTONEXT(started_procs))
	{
		pid = LCONT(started_procs, pid_t*);
		waitpid(*pid, NULL, 0);
	}
	ft_lstdel(&g_shdata.started_procs, &std_mem_del);

	if (errno)
	{
		if (errno == ECHILD || errno == EINTR)
			errno = 0;
		else
			ft_err_erno(errno, TRUE);
	}
}
