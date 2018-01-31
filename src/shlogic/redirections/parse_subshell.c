/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:17 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:17 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static void	child_life_(t_cmd_env *cmd_env)
{
	dup_and_close(cmd_env->fd_io.in, STDIN_FILENO, FALSE);
	dup_and_close(cmd_env->fd_io.out, STDOUT_FILENO, FALSE);
	dup_and_close(cmd_env->fd_io.err, STDERR_FILENO, FALSE);
	dup_and_closelst(cmd_env->fd_io.other, FALSE);

	t_str		raw_in;
	t_sub_sh	sub_shell;

	raw_in = ft_strnew(ft_strlen(cmd_env->argv[0]) + 1);
	ft_strcpy(raw_in, ft_strchr(cmd_env->argv[0], '(') + 1);

	if (ft_strlen(raw_in) <= 1)
		ft_error(TRUE, "syntax error near unexpected token `)'");

	raw_in[ft_strlen(raw_in) - 1] = '\n';
	g_shdata.is_term = FALSE;
	
	events_remove_with_key(g_events, "at_exit_restore_term");

	sub_shell.raw_cmd = raw_in;
	sub_shell.fd_io = cmd_env->fd_io;

	g_shdata.sub_sh = ft_memdup(&sub_shell, sizeof(sub_shell));
}

pid_t		parse_subshell(t_cmd_env *cmd_env)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		ft_err_erno(errno, TRUE);

	if (pid == CHILD_PROCESS_PID)
	{
		child_life_(cmd_env);
		return -2;
	}
	else
	{
		ft_lstadd(&g_shdata.started_procs, ft_lstnew(&pid, sizeof(pid)));
		return 0;
	}
}
