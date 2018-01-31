/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_schedule.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:55 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:55 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"

void			remove_schedule(t_alrm_schedl *schedule)
{
	t_lst_schedl	*match;

	match = ft_lst_first(g_taskmast.schedules, schedule, sizeof(schedule),
		&std_lst_cont_ptr_cmp);

	if (match)
		ft_lstrm(&g_taskmast.schedules, match, &std_mem_del);
}
