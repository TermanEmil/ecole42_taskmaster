/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_proc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:12 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:12 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"

void	del_proc(t_process *proc)
{
	close_process_open_fds(proc);
	if (proc->config)
		del_proc_config(proc->config);
	ft_memdel((void**)&proc->name);
	free(proc);	
}
