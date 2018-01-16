#include "taskmaster42.h"

static t_rostr	get_atempts_str_(const t_process *proc)
{
	static char	buf[32];
	t_rostr		color;

	ft_bzero(buf, sizeof(buf));
	if (ISSTATE(proc, e_critic))
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

t_rostr		get_proc_description(const t_process *proc)
{
	static char		buf[124];

	ft_bzero(buf, sizeof(buf));
	if (proc->status.state == e_not_started)
		ft_strcpy(buf, C_GRAY "-------" C_EOC);
	else if (ISSTATE(proc, e_critic) || ISSTATE(proc, e_completed))
	{
		ft_sprintf(buf, "ex_stat: %d %s%s, %s",
			proc->status.waitpid_status,
			get_sig_on_kill_str_(proc),
			proc_struptime(proc),
			get_atempts_str_(proc));
	}
	else
	{
		ft_sprintf(buf, "%s, %s",
			proc_struptime(proc),
			get_atempts_str_(proc));
	}
	return buf;
}