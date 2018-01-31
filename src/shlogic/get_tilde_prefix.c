/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tilde_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:28 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:28 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shlogic.h"

/*
** Get the prefix of the tilde. The prev of the given key is tilde.
** Used to process the tilde.
*/

t_str	get_tilde_prefix(const t_lst_inkey *keys, int *len)
{
	const t_sh_inkey	*sh_inkey;
	const t_lst_inkey	*start;
	int					count;

	start = keys;	
	for (count = 0; keys; LTONEXT(keys), count++)
	{
		sh_inkey = LCONT(keys, t_sh_inkey*);
		if (sh_inkey == NULL)
			break;
		if (sh_inkey->inside_of == CHAR_PARENTHESIS_LIM ||
			ft_strstr(" \t/", sh_inkey_get_meaning(sh_inkey)))
		{
			break;
		}
	}

	*len = count;
	return ft_lst_njoin(
		start,
		(t_rostr (*)(const void*, size_t))&sh_inkey_get_meaning, NULL, count);
}
