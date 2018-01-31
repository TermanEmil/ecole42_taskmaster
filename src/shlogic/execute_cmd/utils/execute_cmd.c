/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:32 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:32 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shlogic.h"
#include "shell42.h"

pid_t		execute_cmd(t_cmd_env *cmd_env, t_rostr cmd_path)
{
	pid_t	pid;
	t_str	*env_tab;

	pid = fork();
	if (pid == -1)
		ft_err_erno(errno, TRUE);

	if (pid == CHILD_PROCESS_PID)
	{
		dup_and_close(cmd_env->fd_io.in, STDIN_FILENO, TRUE);
		dup_and_close(cmd_env->fd_io.out, STDOUT_FILENO, TRUE);
		dup_and_close(cmd_env->fd_io.err, STDERR_FILENO, TRUE);

		dup_and_closelst(cmd_env->fd_io.other, TRUE);

		env_tab = shvars_form_key_val_tab(cmd_env->shvars->env);
		if (execve(cmd_path, cmd_env->argv, env_tab) == -1)
		{
			ft_error(TRUE, "%s: %s: %s\n",
				g_proj_name, cmd_env->argv[0], strerror(errno));
		}
	}
	else
		ft_lstadd(&g_shdata.started_procs, ft_lstnew(&pid, sizeof(pid)));

	return pid;
}
