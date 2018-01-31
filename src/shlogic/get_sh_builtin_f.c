/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sh_builtin_f.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:24 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:24 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shlogic.h"

t_exec_cmd_f	*get_sh_builtin_f(t_rostr cmd, const t_hashtab *built_in_cmds)
{
	t_hashmem	htab_match;

	if (cmd == NULL)
		return NULL;

	htab_match = htab_get_val(built_in_cmds, new_hashmem_str((t_str)cmd));

	if (htab_match.mem == NULL)
		return NULL;
	else
		return htab_match.mem;
}
