#include "taskmaster42.h"
#include <signal.h>

static int	print_help_()
{
	ft_putstr("restart [<program name> | PID<program pid> | state].\n"
		"Wildcards included.\n");
	return 0;
}

static void	restart_process_(t_process *proc)
{
	t_bool	will_be_auto_restarted;

	if (ISSTATE(proc, e_not_started))
	{
		ft_prerror(FALSE, "restart: %s: can't restart not started program.\n",
			proc->name);
		return;
	}
	
	ft_printf("Restarting %s.\n", proc->name);
	if (ISSTATE(proc, e_running) || ISSTATE(proc, e_stopped))
	{
		will_be_auto_restarted = proc_has_to_be_restarted(proc, SIGKILL, TRUE);

		ft_printf("\tKilling %s.\n", proc->name);
		if (kill_proc(SIGKILL, proc) != 0)
			return;

		if (!will_be_auto_restarted)
			restart_process(proc);
	}
	else
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
	return 0;
}