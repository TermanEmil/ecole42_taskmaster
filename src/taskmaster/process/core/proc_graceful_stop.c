#include "taskmaster42.h"
#include <time.h>

static t_process	new_grace_stop_proc_(const t_process *proc)
{
	t_process	result;
	t_str		tmp_name;

	ft_memcpy(&result, proc, sizeof(result));
	tmp_name = ft_strmegajoin(2, proc->name, "_grace_stop");
	result.name_id = new_unique_name_id(tmp_name, g_taskmast.procs);
	result.name = new_process_name(tmp_name, result.name_id);
	ft_memdel((void**)&tmp_name);
	return result;
}

static void			log_actions_(
						const t_process *target_proc,
						const t_process *stopping_proc)
{
	TASKMAST_LOG("Graceful stop process: %s PID %d has been set for %s, "
		"which will get sigkilled in %ds\n",
		stopping_proc->name,
		stopping_proc->pid,
		target_proc->name,
		stopping_proc->config->time_before_forced_kill);	
}

static void			set_stop_proc_stats_(
						t_process *stopping_proc,
						const t_process *target_proc)
{
	stopping_proc->status.state = e_grace_stopping;
	stopping_proc->config = proc_config_dup(target_proc->config);
	stopping_proc->proc_time.start_time = time(NULL);
	stopping_proc->proc_time.running_time = 0;
	stopping_proc->proc_time.finish_time = 0;
}

static void			set_alarm_(const t_process *stopping_proc)
{
	setup_alarm(&g_taskmast,
		new_alarm_schedule(
			stopping_proc->pid,
			time(NULL) + stopping_proc->config->time_before_forced_kill,
			&sigkill_pid));
}

/*
** Creates a new process entry, with the given proc->pid and subscribes it to
** the timer to be killed if it doesn't stop by itself in
** proc->config->time_before_forces_kill.
** A proc->config->sig_graceful_stop signal is sent to the given proc.
** The given proc is set to completed, with pid = -1.
*/

void				proc_graceful_stop(t_process *proc)
{
	t_process	stop_proc;
	pid_t		pid_save;

	if (lst_proc_pidof_grac_stop(g_taskmast.procs, proc->pid))
		return;
	stop_proc = new_grace_stop_proc_(proc);
	discard_proc_redirs(proc);
	set_stop_proc_stats_(&stop_proc, proc);

	ft_lstadd(&g_taskmast.procs, ft_lstnew(&stop_proc, sizeof(stop_proc)));
	log_actions_(proc, &stop_proc);

	pid_save = proc->pid;
	proc->pid = -1;
	proc->status.state = e_completed;

	set_alarm_(&stop_proc);
	raw_proc_kill(proc->config->sig_graceful_stop,
		pid_save, proc->name, proc_struptime(proc));

	update_alarm();
}