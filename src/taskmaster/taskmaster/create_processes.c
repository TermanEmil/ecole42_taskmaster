#include "taskmaster42.h"

void	create_processes(t_taskmast *taskmast, t_lst_proccfg *proc_cfgs)
{
	t_proc_config	*config;
	t_process		proc;
	int				i;

	for (; proc_cfgs; LTONEXT(proc_cfgs))
	{
		config = LCONT(proc_cfgs, t_proc_config*);
		for (i = 0; i < config->nb_of_procs; i++)
		{
			proc = new_process(config, taskmast->procs);
			ft_lstadd(&taskmast->procs, ft_lstnew(&proc, sizeof(proc)));
			TASKMAST_LOG("Process %s created\n", proc.name);
		}
	}
}
