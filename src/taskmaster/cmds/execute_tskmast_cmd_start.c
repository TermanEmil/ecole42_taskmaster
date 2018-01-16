#include "taskmaster42.h"

static int	basic_case_(const t_str *argv)
{
	if (ft_tab_len((const void**)argv) == 1 || ft_strequ(argv[1], "-h"))
	{
		ft_putstr("start -h PID131213 my_program_1\n"
			"The not started programs are started, the others are forcefully "
			"restarted\n");
		return 0;
	}
	return 1;
}

int			execute_tskmast_cmd_start(t_cmd_env *cmd_env)
{
	const t_str		*argv;
	t_process		*proc;
	int				ret;

	argv = cmd_env->argv;
	if ((ret = basic_case_(argv)) != 1)
		return ret;

	argv++;
	for (; *argv; argv++)
	{
		if ((proc = get_process_from_strcmd(g_taskmast.procs, *argv)) == NULL)
			ft_prerror(FALSE, "start: %s Invalid pid or process name\n", *argv);
		else
		{
			if (ISSTATE(proc, e_not_started))
				process_start(proc);
			else
				restart_process(proc);
		}
	}
	return 0;
}