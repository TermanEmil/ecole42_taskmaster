/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_inkey_get_pure_meaning.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:33 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:33 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

/*
** Returns the meaning of the key if it's a true char, else - an empty string.
*/

t_rostr	sh_inkey_get_pure_meaning(t_sh_inkey const * const key)
{
	if (key == NULL)
		return ("");
	else
		return (sh_inkey_get_meaning(key));
}
