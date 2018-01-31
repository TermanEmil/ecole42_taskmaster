/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_inkey_get_meaning.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:33 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:33 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

/*
** Returns the meaning part of a given key. If meaning is null, then it's the
** same as the displayable.
*/

char	*sh_inkey_get_meaning(t_sh_inkey const * const target)
{
	if (target == NULL)
		return ("");
	else if (target->meaning)
		return (target->meaning);
	else
		return (target->displayed_chars);
}
