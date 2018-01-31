/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process_name_id.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:09 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:09 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"

int		get_process_name_id(
			t_rostr proc_prog_name,
			const t_lst_proc *proccesses)
{
	int				max;
	const t_process *aux;

	max = 0;
	for (; proccesses; LTONEXT(proccesses))
	{
		aux = LCONT(proccesses, const t_process*);
		if (ft_strequ(aux->config->prog_name, proc_prog_name))
			if (max <= aux->name_id)
				max = aux->name_id + 1;
	}
	return max;
}
