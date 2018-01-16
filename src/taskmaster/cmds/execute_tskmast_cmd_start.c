#include "taskmaster42.h"

int		execute_tskmast_cmd_start(t_cmd_env *cmd_env)
{
	const t_str		*argv;
	t_process		*proc;

	argv = cmd_env->argv;
	if (ft_tab_len((const void**)argv) == 1)
	{
		ft_prerror(FALSE, "start: At least one argument is expected\n");
		return -1;
	}

	argv++;
	for (; *argv; argv++)
	{
		proc = lst_get_proc_with_pidname(g_taskmast.procs, *argv);
		if (proc == NULL)
			proc = lst_get_proc_with_name(g_taskmast.procs, *argv);
		if (proc == NULL)
			ft_prerror(FALSE, "start: %s Invalid pid or process name\n", *argv);
		else
			switch (proc->status.state)
			{
				case e_not_started:
					process_start(proc);
					break;
				case e_completed:
				case e_stopped:
				case e_critic:
				case e_running:
					restart_process(proc);
					break;
			}
	}
	return 0;
}