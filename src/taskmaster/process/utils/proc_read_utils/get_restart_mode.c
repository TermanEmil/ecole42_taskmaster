#include "config_reader_.h"

t_restart_mode		get_restart_mode(t_str line)
{
	t_str	val;

	val = ft_strchr(line, '=') + 1;
	if (ft_strequ(val, "always"))
		return e_always;
	else if (ft_strequ(val, "never"))
		return e_never;
	else if (ft_strequ(val, "unexpected_exit"))
		return e_unexpected_exit;
	else
		ft_prerror(FALSE, "config file: Invalid restart mode: %s\n", val);
	return e_never;
}
