/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_get_key_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:46 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:46 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

/*
** Returns the first and the largest match from
** get_shdata()->input.key_cmds->tab with key_str (starting from 0).
*/

t_hashpair const	*shell_get_key_cmd(char const * const key_str)
{
	t_hashpair 			**key_cmds;
	size_t				i;
	t_hashpair			*result;

	key_cmds = g_shinput->key_cmds->tab;
	result = NULL;
	for (i = 0; i < g_shinput->key_cmds->tablen; i++)
	{
		if (key_cmds[i])
			if (ft_strnequ(key_str, (char*)key_cmds[i]->key.mem,
				ft_strlen((char*)key_cmds[i]->key.mem)))
			{
				if (result == NULL)
					result = key_cmds[i];
				else if (ft_strlen((char*)key_cmds[i]->key.mem) >
					ft_strlen(result->key.mem))
				{
					result = key_cmds[i];
				}
			}
	}
	return (result);
}
