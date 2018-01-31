/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:24 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:24 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellvars.h"

t_rostr		get_shvar(t_rostr key, const t_shvars *shvars)
{
	t_rostr	value;

	value = htab_get_strval(shvars->local, new_hashmem_str((t_str)key));
	if (value == NULL)
		value = htab_get_strval(shvars->env, new_hashmem_str((t_str)key));
	return value;
}
