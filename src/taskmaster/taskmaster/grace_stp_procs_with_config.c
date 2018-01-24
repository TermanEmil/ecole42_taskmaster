#include "taskmaster42.h"

/*
** Destroy the processes with the given config. Only a maximum of nb_of_procs
** can be destroyed from a config.
*/

void	grace_stp_procs_with_config(
			t_taskmast *taskmast,
			const t_proc_config *cfg)
{
	t_lst_proc		*next;
	t_lst_proc		*iter;
	t_process		*proc;
	int				nb_of_procs;

	nb_of_procs = cfg->nb_of_procs;
	for (iter = taskmast->procs; iter; iter = next)
	{
		next = LNEXT(iter);
		proc = LCONT(iter, t_process*);

		if (nb_of_procs > 0 && proc->config->hash == cfg->hash)
		{
			if (ISSTATE(proc, e_grace_stopping))
				continue;

			destroy_proc_intance(taskmast, proc);
			nb_of_procs--;
		}
	}
}
