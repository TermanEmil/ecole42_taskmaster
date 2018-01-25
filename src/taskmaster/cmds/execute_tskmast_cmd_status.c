#include "taskmaster42.h"
#include <sys/types.h>
#include <signal.h>
#include <time.h>

#define STATE_LEN_ 24
#define DESCRIPT_LEN_ 64
#define PROC_NAME_LEN_ 64
#define PID_LEN_ 9

static int		print_help_()
{
	ft_putstr(
		"status [<process_name> | PID<process pid> | <process_state>]\n"
		"Wildcards included.\n");
	return 0;
}

static void		print_proc_status_(const t_process *proc)
{
	t_rostr		strstate;

	if (proc == NULL)
		return;
	
	strstate = get_proc_state_str(proc);
	ft_printf("%*s %*s %*s %-*d\n",
		STATE_LEN_, strstate,
		DESCRIPT_LEN_, get_proc_description(proc),
		PROC_NAME_LEN_, proc->name,
		PID_LEN_, proc->pid);
}

static void		print_status_of_the_argv_(const t_str *argv)
{
	argv++;
	for (; *argv; argv++)
	{
		execute_function_from_strcmd(*argv, g_taskmast.procs, "status:",
			(void (*)(t_process*))&print_proc_status_);
	}
}

static void		print_informative_bar_()
{
	size_t	color_len;

	color_len = ft_strlen(C_RED) + ft_strlen(C_EOC);
	ft_printf("%*s %*s %*s %-*s\n",
		STATE_LEN_ - ft_strlen(C_EOC), C_LMAGENTA "State",
		DESCRIPT_LEN_ - color_len, "Description",
		PROC_NAME_LEN_, "Name",
		PID_LEN_ + ft_strlen(C_LMAGENTA), "PID" C_EOC);
}

int				execute_tskmast_cmd_status(t_cmd_env *cmd_env)
{
	taskmast_parse_signals();
	g_taskmast.signal_flags.its_safe = FALSE;
	if (cmd_env->argv[1] != NULL)
	{
		if (ft_strequ(cmd_env->argv[1], "-h"))
			return print_help_();
	}
	else
		print_general_status(g_taskmast.procs);

	print_informative_bar_();
	if (cmd_env->argv[1] != NULL)
		print_status_of_the_argv_(cmd_env->argv);
	else
		ft_lstiter_mem(g_taskmast.procs, (void (*)(void*))&print_proc_status_);
	g_taskmast.signal_flags.its_safe = TRUE;
	taskmast_parse_signals();
	return 0;
}
