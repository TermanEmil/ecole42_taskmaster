/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_input_destruct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:30 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:30 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

void			current_input_destruct(t_current_input * const target)
{
	if (target)
	{
		shinput_seq_destruct(target->input);
	}
}
