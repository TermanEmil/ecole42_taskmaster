#include "taskmaster42.h"

static t_rostr	get_atempts_str_(const t_process *proc, t_rostr state_str)
{
	static char	buf[32];
	t_rostr		color;

	ft_bzero(buf, sizeof(buf));
	if (ft_strequ(state_str, STATE_CRITIC))
		color = C_RED;
	else
		color = C_GREEN;
	ft_sprintf(buf, "%s%d/%d" C_EOC,
		color, proc->status.attempt, proc->config->restart_attempts);
	return buf;
}

static t_rostr	get_sig_on_kill_str_(const t_process *proc)
{
	static char	buf[32];

	if (proc->status.sig_on_kill != 0)
	{
		ft_strcpy(buf, strsignal(proc->status.sig_on_kill));
		ft_strcat(buf, " ");
	}
	else
		buf[0] = '\0';
	return buf;
}

t_rostr		get_proc_description(const t_process *proc, t_rostr state_str)
{
	static char		buf[124];

	ft_bzero(buf, sizeof(buf));
	if (ft_strequ(state_str, STATE_NOT_STARTED))
		ft_strcpy(buf, C_GRAY "-------" C_EOC);
	else if (ft_strstr(STATE_CRITIC STATE_COMPLETED, state_str))
	{
		ft_sprintf(buf, "ex_stat: %d %s%s, %s",
			proc->status.waitpid_status,
			get_sig_on_kill_str_(proc),
			proc_struptime(proc),
			get_atempts_str_(proc, state_str));
	}
	else
	{
		ft_sprintf(buf, "%s, %s",
			proc_struptime(proc),
			get_atempts_str_(proc, state_str));
	}
	return buf;
}
