/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_elapsed_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:14 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:14 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  999:99:99
*/

t_rostr	str_elapsed_time(int elapsed_time)
{
	static char		buf[32];
	int				hours;
	int				mins;
	int				secs;

	hours = elapsed_time / (60 * 60);
	elapsed_time = elapsed_time % (60 * 60);
	mins = elapsed_time / 60;
	elapsed_time = elapsed_time % 60;
	secs = elapsed_time;
	ft_bzero(buf, sizeof(buf));
	ft_sprintf(buf, "%02d:%02d:%02d", hours, mins, secs);
	return buf;
}
