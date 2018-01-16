#include "process42.h"

void			execute_function_from_strcmd(
					t_rostr cmd,
					t_lst_proc *procs,
					t_rostr err_msg,
					void (*f)(t_process*))
{
	enum e_proc_state	state;
	t_lst_proc			*procs_buf;

	procs_buf = get_processes_from_strcmd(procs, cmd);
	if (procs_buf)
	{
		ft_lstiter_mem(procs_buf, (void (*)(void*))f);
		ft_lstdel(&procs_buf, NULL);
	}
	else if ((state = get_state_from_str(cmd)) != 0)
	{
		procs_buf = ft_lst_filter(procs, &state,
			sizeof(state), (t_lst_cont_cmp*)&proc_is_state);
		ft_lstiter_mem(procs_buf, (void (*)(void*))f);
		ft_lstdel(&procs_buf, NULL);
	}
	else
		ft_prerror(FALSE, "%s Invalid pid, process name or state\n", err_msg);
}
