/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tskmast_cmd_stop.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:13 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:13 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"
#include <signal.h>

static int	print_help_()
{
	ft_putstr("stop [<program name> | PID<program pid> | <state>]\n"
		"Wildcards included.\n");
	return 0;
}

static void	stop_process_(t_process *proc)
{
	if (proc == NULL)
		return;

	ft_printf("Stopping %s.\n", proc->name);
	stop_process(proc);
}

int			execute_tskmast_cmd_stop(t_cmd_env *cmd_env)
{
	int		i;

	while (!g_taskmast.signal_flags.its_safe)
		usleep(SIGSAFE_CHECK_INTERVAL);
	
	g_taskmast.signal_flags.its_safe = FALSE;
	if (cmd_env->argv[1] == NULL || ft_strequ(cmd_env->argv[1], "-h"))
		return print_help_();
	
	for (i = 1; cmd_env->argv[i]; i++)
	{
		execute_function_from_strcmd(cmd_env->argv[i], g_taskmast.procs,
			"stop:", (void (*)(t_process*))&stop_process_);
	}
	g_taskmast.signal_flags.its_safe = TRUE;
	taskmast_parse_signals();
	return 0;
}
