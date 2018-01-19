#include "taskmaster42.h"

/*
** Destroy the processes with the given config. Only a maximum of nb_of_procs
** can be destroyed from a config.
*/

void	destroy_procs_with_config(
			t_taskmast *taskmast,
			const t_proc_config *cfg)
{
	t_lst_proc		*next;
	t_lst_proc		*iter;
	t_proc_config	*proc_cfg;
	int				nb_of_procs;

	nb_of_procs = cfg->nb_of_procs;
	for (iter = taskmast->procs; iter;)
	{
		next = LNEXT(iter);
		proc_cfg = LCONT(iter, t_process*)->config;
		if (nb_of_procs > 0 && proc_cfg->hash == cfg->hash)
		{
			if (ISSTATE(LCONT(iter, t_process*), e_grace_stopping))
				continue;

			destroy_proc_intance(taskmast, LCONT(iter, t_process*));
			nb_of_procs--;
		}
		iter = next;
	}
}
