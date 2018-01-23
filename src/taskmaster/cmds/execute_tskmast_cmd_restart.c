
#include "taskmaster42.h"
#include <signal.h>

static int	print_help_()
{
	ft_putstr("restart [<program name> | PID<program pid> | state].\n"
		"Wildcards included.\n");
	return 0;
}

static int	parse_execeptions_(t_process *proc)
{
	switch (proc->status.state)
	{
		case e_not_started:
			ft_prerror(FALSE, "restart: %s: can't restart not started "
				"program.\n", proc->name);
			return 1;
		
		case e_stopped:
			ft_prerror(FALSE, "restart: %s: can't restart stopped processes.\n",
				proc->name);
			return 1;

		case e_grace_stopping:
			ft_prerror(FALSE, "restart: %s: can't restart processes that are "
				"being gracefully stopped.\n", proc->name);
			return 1;

		default:
			return 0;
	}
}

static void	restart_process_(t_process *proc)
{
	t_bool	will_be_auto_restarted;

	if (parse_execeptions_(proc) != 0)
		return;

	will_be_auto_restarted =
		proc_has_to_be_restarted(proc, proc->config->sig_graceful_stop, TRUE);

	ft_printf("Restarting %s.\n", proc->name);
	if (ISSTATE(proc, e_running) || ISSTATE(proc, e_stopped))
		proc_graceful_stop(proc);

	// if (!will_be_auto_restarted)
	restart_process(proc);
}

int			execute_tskmast_cmd_restart(t_cmd_env *cmd_env)
{
	int		i;

	if (cmd_env->argv[1] == NULL || ft_strequ(cmd_env->argv[1], "-h"))
		return print_help_();

	for (i = 1; cmd_env->argv[i]; i++)
	{
		execute_function_from_strcmd(cmd_env->argv[i], g_taskmast.procs,
			"restart:", (void (*)(t_process*))&restart_process_);
	}
	update_alarm();
	return 0;
}