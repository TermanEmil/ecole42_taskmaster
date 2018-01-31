/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_inkey_get_symbols.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:35 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:35 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

/*
** Returns the number of symbols the given key->displayed_chars has
*/

size_t	sh_inkey_get_symbols(t_sh_inkey const * const key)
{
	if (char_is_utf8((t_uchar*)key->displayed_chars))
		return (1);
	else
		return (ft_strlen(key->displayed_chars));
}
