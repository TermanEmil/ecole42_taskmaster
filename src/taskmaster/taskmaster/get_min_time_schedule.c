/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_min_time_schedule.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:50 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:50 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"

static int		schedule_get_time_(const t_alrm_schedl *schedule)
{
	return schedule->tm;
}

t_alrm_schedl	*get_min_time_schedule(const t_lst_schedl *schedules)
{
	t_lst_schedl	*lmin;
	t_alrm_schedl	*result;

	if (schedules == NULL)
		return NULL;

	lmin = ft_lst_min(schedules, (int (*)(void*))&schedule_get_time_);
	result = (lmin == NULL) ? NULL : LCONT(lmin, t_alrm_schedl*);
	return result;
}
