#include "config_reader_.h"

t_bool		parse_std_out_err(t_str line, t_proc_config *proc_config)
{
	t_str	val;

	val = ft_strchr(line, '=') + 1;
	if (ft_str_starts_with(line, "stdout="))
	{
		if (proc_config->stdout)
			free(proc_config->stdout);
		proc_config->stdout = ft_strdup(val);
	}
	else if (ft_str_starts_with(line, "stderr="))
	{
		if (proc_config->stderr)
			free(proc_config->stderr);
		proc_config->stderr = ft_strdup(val);
	}
	else
		return FALSE;
	return TRUE;
}