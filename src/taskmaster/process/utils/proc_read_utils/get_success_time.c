/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_success_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:03 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:03 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config_reader_.h"

int			get_success_time(t_rostr val)
{
	int		intval;

	intval = (val == NULL || ft_strequ(val, "")) ? 0 : ft_atoi(val);
	if (intval < 0)
	{
		TASKMAST_ERROR(FALSE, "Success time = %d can't be negative.\n", intval);
		return -1;
	}
	else
		return intval;
}
