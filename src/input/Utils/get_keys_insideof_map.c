/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_keys_insideof_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:42 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:42 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

/*
** Make a string of 'inside_of' value of each key.
*/

t_str	get_keys_insideof_map(t_lst_inkey *keys)
{
	t_str	result;
	int		i;

	result = ft_strnew(ft_lstlen(keys));
	for (i = 0; keys; LTONEXT(keys))
		if (keys->content)
			result[i++] = LCONT(keys, t_sh_inkey*)->inside_of;
	return result;
}
