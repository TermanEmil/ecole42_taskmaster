#include "taskmaster42.h"
#include <sys/types.h>
#include <signal.h>
#include <time.h>

#define STATE_LEN_ 24
#define DESCRIPT_LEN_ 64
#define PROC_NAME_LEN_ 64
#define PID_LEN_ 9

static void		print_proc_status_(const t_process *proc)
{
	t_rostr		strstate;

	strstate = get_proc_state_str(proc);
	ft_printf("%*s %*s %*s %-*d\n",
		STATE_LEN_, strstate,
		DESCRIPT_LEN_, get_proc_description(proc),
		PROC_NAME_LEN_, proc->name,
		PID_LEN_, proc->pid);
}

void			print_schedule_delta_time(t_alrm_schedl *schedule)
{
	ft_printf("delta = %d\n", schedule->tm - time(NULL));
}

static void		print_general_status_(const t_lst_proc *procs)
{
	int				running;
	int				finished;
	int				stopped;
	int				failed;
	int				total;
	const t_process	*proc;

	running = 0;
	finished = 0;
	stopped = 0;
	failed = 0;
	total = ft_lstlen(procs);
	for (; procs; LTONEXT(procs))
	{
		proc = LCONT(procs, t_process*);
		running += ISSTATE(proc, e_running);
		finished += ISSTATE(proc, e_completed);
		failed += ISSTATE(proc, e_critic);
		stopped += ISSTATE(proc, e_stopped);
	}
	ft_printf(
		"Running: %d, Completed: %d, Critic: %d, Stopped: %d, Total: %d\n",
		running, finished, failed, stopped, total);


	ft_printf("Schedules len: %d\n", ft_lstlen(g_taskmast.schedules));
	ft_lstiter_mem(g_taskmast.schedules, (void (*)(void*))&print_schedule_delta_time);
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

static int		print_help_()
{
	ft_putstr(
		"status [<process_name> | PID<process pid> | <process_state>]\n"
		"Wildcards included.\n");
	return 0;
}

int				execute_tskmast_cmd_status(t_cmd_env *cmd_env)
{
	size_t		color_len;

	if (cmd_env->argv[1] != NULL)
	{
		if (ft_strequ(cmd_env->argv[1], "-h"))
			return print_help_();
	}
	else
		print_general_status_(g_taskmast.procs);

	color_len = ft_strlen(C_RED) + ft_strlen(C_EOC);
	ft_printf("%*s %*s %*s %-*s\n",
		STATE_LEN_ - ft_strlen(C_EOC), C_LMAGENTA "State",
		DESCRIPT_LEN_ - color_len, "Description",
		PROC_NAME_LEN_, "Name",
		PID_LEN_ + ft_strlen(C_LMAGENTA), "PID" C_EOC);

	if (cmd_env->argv[1] != NULL)
		print_status_of_the_argv_(cmd_env->argv);
	else
		ft_lstiter_mem(g_taskmast.procs, (void (*)(void*))&print_proc_status_);
	return 0;
}
