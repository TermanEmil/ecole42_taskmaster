#include "shellvars.h"

t_rostr		get_shvar(t_rostr key, const t_shvars *shvars)
{
	t_rostr	value;

	value = htab_get_strval(shvars->local, new_hashmem_str((t_str)key));
	if (value == NULL)
		value = htab_get_strval(shvars->env, new_hashmem_str((t_str)key));
	return value;
}
