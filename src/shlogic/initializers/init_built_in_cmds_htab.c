/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_built_in_cmds_htab.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:25 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:25 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "taskmaster42.h"

static void		add_cmd_(t_hashtab *htab, t_rostr cmd_name, const void *f)
{
	hashtab_add_pair(htab,
		new_hashpair_mllc(
			new_hashmem_str((t_str)cmd_name),
			new_hashmem((void*)f, sizeof(f))));
}

t_hashtab		*init_built_in_cmds_htab()
{
	t_hashtab	*htab;

	htab = new_hashtab(16, NULL, NULL);
	add_cmd_(htab, "exit", (t_exec_cmd_f*)&execute_cmd_exit);
	add_cmd_(htab, "cd", &execute_cmd_cd);
	add_cmd_(htab, "env", &execute_cmd_env);
	add_cmd_(htab, "setenv", &execute_cmd_setenv);
	add_cmd_(htab, "export", &execute_cmd_setenv);
	add_cmd_(htab, "unsetenv", &execute_cmd_unsetenv);
	add_cmd_(htab, "unset", &execute_cmd_unsetenv);

	add_cmd_(htab, "status", &execute_tskmast_cmd_status);
	add_cmd_(htab, "start", &execute_tskmast_cmd_start);
	add_cmd_(htab, "stop", &execute_tskmast_cmd_stop);
	add_cmd_(htab, "restart", &execute_tskmast_cmd_restart);
	return htab;
}
