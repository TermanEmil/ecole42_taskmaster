/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shvars_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:25 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:25 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellvars.h"

void		shvars_destroy(t_shvars *shvars)
{
	if (shvars->env != NULL)
		del_hashtab(&shvars->env);
	if (shvars->local != NULL)
		del_hashtab(&shvars->local);
}
