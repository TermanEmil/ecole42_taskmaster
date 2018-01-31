/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_process_open_fds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:07 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:07 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process42.h"
#include "taskmaster42_utils_.h"

static void		close_positive_fds_(int *fds)
{
	close_if_open(&fds[0]);
	close_if_open(&fds[1]);
}

void			close_process_open_fds(t_process *process)
{
	close_positive_fds_(process->stdin_fd);
	close_positive_fds_(process->stdout_fd);
	close_positive_fds_(process->stderr_fd);
}
