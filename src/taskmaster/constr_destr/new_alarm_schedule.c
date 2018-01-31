/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_alarm_schedule.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:15 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:15 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"

t_alrm_schedl	new_alarm_schedule(
					pid_t pid,
					int schedule_time,
					void (*f)(t_taskmast*, pid_t))
{
	t_alrm_schedl	result;

	result.pid = pid;
	result.tm = schedule_time;
	result.f = f;
	return result;
}
