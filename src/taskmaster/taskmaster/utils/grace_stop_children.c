#include "taskmaster42.h"

t_bool		proc_terminated(const t_process *proc)
{
	return
		ISSTATE(proc, e_not_started) ||
		ISSTATE(proc, e_completed) ||
		ISSTATE(proc, e_critic);
}

int			running_count_(const t_lst_proc *procs)
{
	const t_lst_proc	*next;
	int					count;

	for (count = 0; procs; procs = next)
	{
		next = LNEXT(procs);
		if (!proc_terminated(LCONT(procs, t_process*)))
			count++;
	}
	return count;
}

static void	grace_stop_not_terminated_(t_process *proc)
{
	if (!proc_terminated(proc))
		proc_graceful_stop(proc);
}

static void	update_exit_status_(const t_taskmast *taskmast)
{
	const char	loading_chars[4] = {'|', '/', '-', '\\'};
	static int	loading_char = 0;
	int			running;
	int			total;
	float		result;

	term_move_cursor_to_left_most();
	term_clear_from_cursor_to_end_line();
	
	running = running_count_(taskmast->procs);
	total = ft_lstlen(taskmast->procs);
	result = (total - running) / (float)total * 100;

	if (running == 0)
	{
		ft_printf("[%s]\n",
			(g_shinput->signaled_sigint) ? "Killed" : "Finished");
	}
	else
	{
		ft_printf("[Finishing[%c]: %.2f%%]>",
			loading_chars[loading_char % sizeof(loading_chars)], result);
	}
	loading_char++;
}

static void	sigkill_proc_(t_process *proc)
{
	kill_proc(SIGKILL, proc);
}

void		grace_stop_children(t_taskmast *taskmast)
{
	t_bool	kill_them;

	kill_them = FALSE;
	TASKMAST_LOG("Gracefult stopping all child processes\n", "");
	ft_lstiter_mem(taskmast->procs, (void (*)())&grace_stop_not_terminated_);
	while (running_count_(taskmast->procs) > 0)
	{
		if (!kill_them && g_shinput->signaled_sigint)
		{
			ft_lstiter_mem(taskmast->procs, (void (*)())&sigkill_proc_);
			kill_them = TRUE;
		}
		taskmast_parse_signals();
		update_exit_status_(taskmast);
		usleep(CHECK_SIG_FLAGS_INTERVAL / 2);
	}
	TASKMAST_LOG("Quit\n", 1);
}
