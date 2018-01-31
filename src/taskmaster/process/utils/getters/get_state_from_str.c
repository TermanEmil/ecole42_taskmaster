/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_state_from_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:07 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:07 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process42.h"

enum e_proc_state	get_state_from_str(t_rostr str)
{
	if (ft_strstr(STATE_NOT_STARTED, str))
		return e_not_started;
	if (ft_strstr(STATE_RUNNING, str))
		return e_running;
	if (ft_strstr(STATE_STOPPED, str))
		return e_stopped;
	if (ft_strstr(STATE_COMPLETED, str))
		return e_completed;
	if (ft_strstr(STATE_CRITIC, str))
		return e_critic;
	if (ft_strstr(STATE_GRACE_STOP, str))
		return e_grace_stopping;
	return 0;
}
