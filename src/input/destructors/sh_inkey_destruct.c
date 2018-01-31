/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_inkey_destruct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:29 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:29 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

void		sh_inkey_destruct(t_sh_inkey * const target)
{
	if (target)
	{
		if (target->displayed_chars)
			free(target->displayed_chars);
		if (target->meaning)
			free(target->meaning);
		free(target);
	}
}
