#include "config_reader_.h"

int			get_success_time(t_rostr val)
{
	int		intval;

	intval = (val == NULL || ft_strequ(val, "")) ? 0 : ft_atoi(val);
	if (intval < 0)
	{
		TASKMAST_ERROR(FALSE, "Success time = %d can't be negative.\n", intval);
		return -1;
	}
	else
		return intval;
}
