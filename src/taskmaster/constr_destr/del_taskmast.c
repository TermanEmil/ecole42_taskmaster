/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_taskmast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:15 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:15 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"
#include "taskmaster42_utils_.h"
#include <signal.h>

void		del_taskmast(t_taskmast *taskmast)
{
	if (taskmast->is_exiting)
		TASKMAST_LOG("Freeing Taskmaster resources\n", "");

	if (taskmast->is_exiting && taskmast->waiter_thread != 0)
	{
		TASKMAST_LOG("Joining the thread\n", 1);
		if (pthread_join(taskmast->waiter_thread, NULL) != 0)
			TASKMAST_ERROR(TRUE, "pthread_join(): %s\n", strerror(errno));
	}

	if (taskmast->is_exiting)
		grace_stop_children(taskmast);

	ft_lstdel(&taskmast->procs, (t_ldel_func*)&del_proc);
	ft_lstdel(&taskmast->proc_cfgs, (t_ldel_func*)&del_proc_config);
	ft_memdel((void**)&taskmast->logger.log_file_path);
	close_if_open(&taskmast->logger.log_file_fd);
	ft_lstdel(&taskmast->schedules, &std_mem_del);
}
