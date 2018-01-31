/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_unique_name_id.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:03 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:03 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process42.h"

int			new_unique_name_id(
				t_rostr default_name,
				const t_lst_proc *procs)
{
	int					max;
	t_rostr				numb_ref;
	const t_lst_proc	*next;
	const t_process		*aux;

	max = 0;
	for (; procs; procs = next)
	{
		next = LNEXT(procs);
		aux = LCONT(procs, t_process*);
		if (ft_str_starts_with(aux->name, default_name))
		{
			numb_ref = aux->name + ft_strlen(default_name) + 1;
			if (ft_str_is_numb(numb_ref))
				max = ft_atoi(numb_ref) + 1;
		}
	}
	return max;
}
