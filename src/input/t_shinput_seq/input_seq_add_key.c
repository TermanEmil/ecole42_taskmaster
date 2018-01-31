/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_seq_add_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:38 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:38 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

void	input_seq_add_key(t_shinput_seq * const target, t_sh_inkey const key)
{
	t_list	*tmp;

	if (target)
	{
		tmp = ft_lstnew(&key, sizeof(key));
		if (tmp == NULL)
			ft_err_mem(1);
		ft_lstadd(&target->keys, tmp);
		target->count++;
	}
}
