#include "taskmaster42.h"

/*
** Given two lists of configs, remove the configs from both lists that have the
** same hash.
*/

static void	remove_the_same_cfgs_(t_lst_proccfg **current, t_lst_proccfg **new)
{
	t_lst_proccfg	*new_i;
	t_lst_proccfg	*matching;
	t_lst_proccfg	*next;

	for (new_i = *new; new_i;)
	{
		matching = ft_lst_first(*current, &LCONT(new_i, t_proc_config*)->hash,
			0, (t_lst_cont_cmp*)&proc_cfg_hash_equ);
		if (matching != NULL)
		{
			next = LNEXT(new_i);
			ft_lstrm(current, matching, NULL);
			ft_lstrm(new, new_i, NULL);
			new_i = next;
		}
		else
			LTONEXT(new_i);
	}
}

/*
** Assign the given processes' configs to the new configs.
*/

static void	update_procs_with_new_configs_(
				t_lst_proc *procs,
				const t_lst_proccfg *new_cfgs)
{
	t_lst_proccfg	*lcfg;

	for (; procs; LTONEXT(procs))
	{
		lcfg = ft_lst_first(new_cfgs, &(LCONT(procs, t_process*))->config->hash,
			0, (t_lst_cont_cmp*)&proc_cfg_hash_equ);
		if (lcfg == NULL) 
			continue;
		LCONT(procs, t_process*)->config = LCONT(lcfg, t_proc_config*);
	}
}

/*
** First, a copy of old and new connfigs are made. Then, the configs with the
** same hash is removed from both lists. After that, destroy the processes that
** have old configs (what's left of it) and add the new processes based on what
** new configs are left.
*/

static void	remove_dead_add_new_procs_(
				t_taskmast *taskmast,
				t_lst_proccfg *old_cfgs,
				t_lst_proccfg *new_cfgs)
{
	t_lst_proccfg	*cpy_old_cfgs;
	t_lst_proccfg	*cpy_new_cfgs;
	t_lst_proc		*new_procs_index;

	cpy_old_cfgs = ft_lstcpy(old_cfgs);
	cpy_new_cfgs = ft_lstcpy(new_cfgs);
	remove_the_same_cfgs_(&cpy_old_cfgs, &cpy_new_cfgs);

	ft_lstiter_mem2(cpy_old_cfgs, taskmast,
		(void (*)(void*, void*))&deactivate_procs_with_config);
	if (cpy_new_cfgs != NULL)
	{
		new_procs_index = ft_lst_get_last(taskmast->procs);
		create_processes(taskmast, cpy_new_cfgs);

		if (new_procs_index == NULL)
			new_procs_index = taskmast->procs;
		else
			LTONEXT(new_procs_index);
		ft_lstiter_mem(new_procs_index, (void (*)(void*))&process_start);
	}
	update_procs_with_new_configs_(taskmast->procs, new_cfgs);

	ft_lstdel(&cpy_old_cfgs, NULL);
	ft_lstdel(&cpy_new_cfgs, NULL);
}

void		reload_procs_config(t_taskmast *taskmast, t_lst_proccfg *new_cfgs)
{
	remove_dead_add_new_procs_(taskmast, taskmast->proc_cfgs, new_cfgs);
	ft_lstdel(&taskmast->proc_cfgs, (t_ldel_func*)&del_proc_config);
	taskmast->proc_cfgs = new_cfgs;
}
