#include "taskmaster42.h"

#define STATE_LEN_ 26
#define DESCRIPT_LEN_ 64
#define PROC_NAME_LEN_ 32

static t_rostr	get_proc_description_(const t_process *proc, t_rostr state_str)
{
	static char		buf[64];
	int				atempt_dif;

	buf[0] = '\0';
	if (state_str == STATE_NOT_STARTED)
		ft_pass();
	else
	{
		atempt_dif = proc->config->restart_attempts - proc->status.attempt;
		ft_sprintf(buf, "pid: %d, uptime: %s, %s%d/%d" C_EOC,
			proc->pid, proc_struptime(proc),
			(atempt_dif <= 0) ? C_RED : C_GREEN,
			proc->status.attempt, proc->config->restart_attempts);
	}
	return buf;
}

static void		print_proc_status_(const t_process *proc)
{
	t_rostr		strstate;

	strstate = get_proc_state_str(proc);
	printf("%*s %*s %*s\n",
		STATE_LEN_, strstate,
		DESCRIPT_LEN_, get_proc_description_(proc, strstate),
		PROC_NAME_LEN_, proc->name);
}

int				execute_tskmast_cmd_status()
{
	const t_lst_proc	*procs;
	size_t				color_len;

	color_len = ft_strlen(C_RED) + ft_strlen(C_EOC);
	ft_printf("%*s %*s %*s\n",
		STATE_LEN_ - color_len, "State",
		DESCRIPT_LEN_ - color_len, "Description",
		PROC_NAME_LEN_, "Name");

	for (procs = g_taskmast.procs; procs; LTONEXT(procs))
		print_proc_status_(LCONT(procs, t_process*));
	return 0;
}
