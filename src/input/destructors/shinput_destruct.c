/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shinput_destruct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:29 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:29 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

void		shinput_destruct(t_shinput * const target)
{
	if (target)
	{
		current_input_destruct(&target->current);
		input_history_destruct(&target->history);
		if (target->term_tty > 0)
			close(target->term_tty);
	}
}
