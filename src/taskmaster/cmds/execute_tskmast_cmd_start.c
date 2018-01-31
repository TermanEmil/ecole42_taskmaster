/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tskmast_cmd_start.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:13 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:13 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"

static int		print_help_()
{
	ft_putstr("start [<program_name> | PID<program pid> | state]\n"
		"Wildcards includes. "
		"The not started programs are started, the stopped are continued.");
	return 0;
}

static void	actual_proc_parsing_(t_process *proc)
{
	if (proc == NULL)
		return;
	
	if (ISSTATE(proc, e_not_started))
	{
		ft_printf("Starting %s\n", proc->name);
		process_start(proc);
	}
	else if (ISSTATE(proc, e_stopped))
	{
		ft_printf("Continuing %s\n", proc->name);
		continue_process(proc);
	}
}

int			execute_tskmast_cmd_start(t_cmd_env *cmd_env)
{
	const t_str		*argv;

	while (!g_taskmast.signal_flags.its_safe)
		usleep(SIGSAFE_CHECK_INTERVAL);

	g_taskmast.signal_flags.its_safe = FALSE;
	argv = cmd_env->argv;
	if (argv[1] == NULL || ft_strequ(argv[1], "-h"))
		return print_help_();

	argv++;
	for (; *argv; argv++)
	{
		execute_function_from_strcmd(
			*argv, g_taskmast.procs, "start:", &actual_proc_parsing_);
	}
	g_taskmast.signal_flags.its_safe = TRUE;
	taskmast_parse_signals();
	return 0;
}
