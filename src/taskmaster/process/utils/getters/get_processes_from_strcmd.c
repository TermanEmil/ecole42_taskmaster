/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_processes_from_strcmd.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:08 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:08 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process42.h"

t_lst_proc	*get_processes_from_strcmd(const t_lst_proc *procs, t_rostr cmd)
{
	t_lst_proc	*buf;
	t_process	*proc;

	if ((proc = lst_get_proc_with_pidname(procs, cmd)) != NULL)
	{
		buf = ft_lstnew_nocpy(proc, sizeof(*proc));
		return buf;
	}
	return lst_get_procs_matching_name(procs, cmd);
}
