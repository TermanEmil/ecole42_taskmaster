/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discard_proc_redirs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:10 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:10 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process42.h"

void		discard_proc_redirs(t_process *proc)
{
	proc->stdin_fd[0] = -1;
	proc->stdin_fd[1] = -1;
	proc->stdout_fd[0] = -1;
	proc->stdout_fd[1] = -1;
	proc->stderr_fd[0] = -1;
	proc->stderr_fd[1] = -1;
}
