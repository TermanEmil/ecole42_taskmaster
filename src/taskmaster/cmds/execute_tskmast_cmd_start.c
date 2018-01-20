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

	argv = cmd_env->argv;
	if (argv[1] == NULL || ft_strequ(argv[1], "-h"))
		return print_help_();

	argv++;
	for (; *argv; argv++)
	{
		execute_function_from_strcmd(
			*argv, g_taskmast.procs, "start:", &actual_proc_parsing_);
	}
	return 0;
}