/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shinput_seq_destruct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:29 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:29 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

void			shinput_seq_destruct(t_shinput_seq * const target)
{
	if (target)
	{
		ft_lstdel(&target->keys, (t_ldel_func*)&sh_inkey_destruct);
		free(target);
	}
}
