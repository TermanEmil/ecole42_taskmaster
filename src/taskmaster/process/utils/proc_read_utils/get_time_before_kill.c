/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_before_kill.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:06 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:06 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config_reader_.h"

void			get_time_before_kill(t_str val, t_proc_config *proc_config)
{
	int		value;

	value = ft_atoi(val);
	if (value < 0)
	{
		TASKMAST_ERROR(FALSE, "time_before_kill = %d: can't be negative. "
			"It will be ignored\n", value);
		proc_config->time_before_forced_kill = -1;
	}
	else
		proc_config->time_before_forced_kill = value;
}
