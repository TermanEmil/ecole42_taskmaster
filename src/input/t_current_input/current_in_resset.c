/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_in_resset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:40 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:40 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

void	current_in_resset(t_current_input * const current_in,
			t_bool const destroy_seq)
{
	if (current_in->input)
	{
		if (destroy_seq)
			shinput_seq_destruct(current_in->input);
		else
			free(current_in->input);
	}

	current_in->input = shinput_seq_new();
	current_in->cursor_pos = 0;
}
