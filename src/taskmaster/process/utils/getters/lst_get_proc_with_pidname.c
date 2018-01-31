/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_get_proc_with_pidname.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:08 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:08 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process42.h"

/*
** Given a pidname in the following format: PID1231231.
*/

t_process	*lst_get_proc_with_pidname(const t_lst_proc* procs, t_rostr pidname)
{
	t_rostr	pid_part;

	if (!ft_str_starts_with(pidname, "PID"))
		return NULL;
	pid_part = pidname + ft_strlen("PID");
	if (!ft_str_is_numb(pid_part))
		return NULL;
	return lst_process_pidof(procs, ft_atoi(pid_part));
}
