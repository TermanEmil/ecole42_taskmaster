#include "taskmaster42.h"
#include <signal.h>

static int	print_help_()
{
	ft_putstr("stop [<program name> | PID<program pid>]\n");
	return 0;
}

int		execute_tskmast_cmd_stop(t_cmd_env *cmd_env)
{
	if (cmd_env->argv[1] == NULL || ft_strequ(cmd_env->argv[1], "-h"))
		return print_help_();
	
	return 0;
}