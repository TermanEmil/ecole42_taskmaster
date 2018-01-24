#include "taskmaster42.h"
#include "regex_tools.h"

static void	load_log_file_(t_taskmast *taskmast, t_rostr val)
{
	if (taskmast->logger.log_file_path)
		free(taskmast->logger.log_file_path);

	taskmast->logger.log_file_path = regex_get_match("[a-zA-Z0-9_./]*", val);
}

int			load_taskmaster_config(t_taskmast *taskmast, t_lst_str *lines)
{
	t_str		line;
	t_str		val;
	int			i;

	taskmast->logger.log_to_term = TRUE;
	for (i = 0; lines; LTONEXT(lines), i++)
	{
		line = LCONT(lines, t_str);

		if (ft_strequ(line, ""))
			break;
		if (ft_strchr(line, ';') != NULL)
			*ft_strchr(line, ';') = '\0';

		val = ft_strchr(line, '=') + 1;
		if (ft_str_starts_with(line, "logfile="))
			load_log_file_(taskmast, val);
		else if (ft_str_starts_with(line, "log_to_term="))
			taskmast->logger.log_to_term = ft_strequ(val, "true");
		else
			TASKMAST_ERROR(FALSE, "%s: Invalid field\n", line);
	}
	return i;
}