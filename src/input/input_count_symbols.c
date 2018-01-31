/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_count_symbols.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:28 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:28 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

/*
** Counts the number of symbols the first n keys of the given list of keys.
*/

size_t				input_count_symbols(t_lst_inkey const *head,
						ssize_t const start, ssize_t const end)
{
	size_t		result;
	ssize_t		i;

	result = 0;
	i = 0;
	while (head)
	{
		if (i > end)
			break;
		if (i >= start)
			result += sh_inkey_get_symbols(LCONT(head, t_sh_inkey*));
		LTONEXT(head);
		i++;
	}
	return (result);
}
