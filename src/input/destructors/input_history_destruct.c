/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_history_destruct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:29 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:29 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

void			input_history_destruct(t_input_history * const target)
{
	if (target)
	{
		ft_lstdel(&target->inputs, (t_ldel_func*)&shinput_seq_destruct);

		if (target->tmp_current_in)
			shinput_seq_destruct(target->tmp_current_in);
	}
}
