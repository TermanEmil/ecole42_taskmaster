/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_alarm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:50 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:50 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"

void	setup_alarm(t_taskmast *taskmast, t_alrm_schedl schedl)
{
	ft_lstadd(&taskmast->schedules, ft_lstnew(&schedl, sizeof(schedl)));
}
