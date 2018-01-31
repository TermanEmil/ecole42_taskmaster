/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_seq_get_disp_len.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:37 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:37 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

/*
** Finds the length of the displayable characters in the given sequence.
*/

size_t	input_seq_get_disp_len(t_shinput_seq const * const seq,
			size_t const starting_with)
{
	size_t		n;
	size_t		i;
	t_lst_inkey	*aux;

	n = 0;
	aux = seq->keys;
	i = 0;
	while (aux)
	{
		if (i >= starting_with)
			n += ft_strlen(LCONT(aux, t_sh_inkey*)->displayed_chars);
		LTONEXT(aux);
		i++;
	}
	return (n);
}
