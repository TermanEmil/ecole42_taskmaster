#include "process42.h"

static t_bool	lst_procs_cmp_pid_(pid_t *pid, const t_process *proc)
{
	return proc->active && proc->pid == *pid;
}

static t_bool	lst_procs_cmp_pid_gace_stop_(pid_t *pid, const t_process *proc)
{
	return proc->active && ISSTATE(proc, e_grace_stopping) && proc->pid == *pid;
}

static t_bool	lst_procs_cmp_pid_no_gace_stop_(
					pid_t *pid,
					const t_process *proc)
{
	return proc->active && !ISSTATE(proc, e_grace_stopping)
		&& proc->pid == *pid;
}

/*
** Find the process with the given pid.
*/

t_process		*lst_process_pidof(const t_lst_proc *procs, pid_t pid)
{
	t_lst_proc	*ret;

	ret = ft_lst_first(
		procs, (void*)&pid, sizeof(pid), (t_lst_cont_cmp*)&lst_procs_cmp_pid_);
	if (ret == NULL)
		return NULL;
	else
		return LCONT(ret, t_process*);
}

t_process		*lst_proc_pidof_no_grac_stop(const t_lst_proc *procs, pid_t pid)
{
	t_lst_proc	*ret;

	ret = ft_lst_first(procs, (void*)&pid, sizeof(pid),
		(t_lst_cont_cmp*)&lst_procs_cmp_pid_no_gace_stop_);
	if (ret == NULL)
		return NULL;
	else
		return LCONT(ret, t_process*);
}

t_process		*lst_proc_pidof_grac_stop(const t_lst_proc *procs, pid_t pid)
{
	t_lst_proc	*ret;

	ret = ft_lst_first(procs, (void*)&pid, sizeof(pid),
		(t_lst_cont_cmp*)&lst_procs_cmp_pid_gace_stop_);
	if (ret == NULL)
		return NULL;
	else
		return LCONT(ret, t_process*);
}
