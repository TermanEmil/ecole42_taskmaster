#include "config_reader_.h"

mode_t		read_umask(t_str umask_strval)
{
	return ft_atoi_base(umask_strval, 8);
}
