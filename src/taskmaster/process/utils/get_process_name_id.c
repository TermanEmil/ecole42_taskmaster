#include "taskmaster42.h"

int		get_process_name_id(const t_process *proc, const t_lst_proc *proccesses)
{
	int				max;
	const t_process *aux;

	max = 0;
	for (; proccesses; LTONEXT(proccesses))
	{
		aux = LCONT(proccesses, const t_process*);
		if (ft_strequ(aux->config->prog_name, proc->config->prog_name))
			if (max <= aux->name_id)
				max = aux->name_id + 1;
	}
	return max;
}
