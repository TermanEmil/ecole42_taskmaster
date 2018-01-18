#include "process42.h"

t_bool	proc_cfg_hash_equ(const size_t *hash, const t_proc_config *config)
{
	return *hash == config->hash;
}

t_bool	proc_ref_equ(const t_process *proc1, const t_process *proc2)
{
	return proc1 == proc2;
}
