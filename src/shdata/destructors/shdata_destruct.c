#include "shell42.h"

void		shdata_destruct(t_shdata * const target)
{
	if (target)
	{
		
		IF_TERM(shinput_destruct(&target->input));
		
		shvars_destroy(&target->shvars);
		del_hashtab(&target->built_in_cmds);
		del_hashtab(&g_shinput->key_cmds);
		
		ft_lstdel(&target->started_procs, &std_mem_del);
	}
}
