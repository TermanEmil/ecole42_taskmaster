#include "taskmaster42.h"

static int		print_help_()
{
	ft_putstr("start [<program_name> | PID<program pid> | state]\n"
		"Wildcards includes. "
		"The not started programs are started, the others are forcefully "
		"restarted\n");
	return 0;
}

static int	basic_case_(const t_str *argv)
{
	if (ft_tab_len((const void**)argv) == 1 || ft_strequ(argv[1], "-h"))
	{
		
		return 0;
	}
	return 1;
}

static void	actual_proc_parsing_(t_process *proc)
{
	if (ISSTATE(proc, e_not_started))
	{
		ft_printf("Starting %s\n", proc->name);
		process_start(proc);
	}
	else
	{
		ft_printf("Restarting %s PID: %d\n", proc->name, proc->pid);
		restart_process(proc);
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