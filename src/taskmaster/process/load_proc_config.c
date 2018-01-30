#include "config_reader_.h"
#include <signal.h>
#include "shell42.h"
#include "regex_tools.h"

#define FREE_ASG_(dest, target)		\
{									\
	if (dest != NULL)				\
		ft_memdel((void**)&dest);	\
	dest = target;					\
}									\

static t_bool		parse_mallocable_fields_(
						t_str line,
						t_proc_config *proc_config)
{
	t_str	val;

	val = ft_strchr(line, '=') + 1;
	if (ft_str_starts_with(line, "command="))
		FREE_ASG_(proc_config->launch_cmd, ft_strdup(val))
	else if (ft_str_starts_with(line, "expected_exit_status="))
	{
		FREE_ASG_(proc_config->expected_exit_statuss,
			get_expected_exit_statuss(line))
	}
	else if (parse_std_out_err(line, proc_config))
		ft_pass();
	else if (ft_str_starts_with(line, "environment="))
	{
		if (proc_config->environment)
			ft_free_bidimens(proc_config->environment);
		proc_config->environment = read_config_environ(val);
	}
	else if (ft_str_starts_with(line, "dir="))
		FREE_ASG_(proc_config->dir, ft_strdup(val))
	else
		return FALSE;
	return TRUE;
}

static t_bool		parse_nonmallocable_fields_(
						t_str line,
						t_proc_config *proc_config)
{
	t_str			val;

	val = ft_strchr(line, '=') + 1;
	if (ft_str_starts_with(line, "nprocs="))
		proc_config->nb_of_procs = ft_atoi(val);
	else if (ft_str_starts_with(line, "autostart="))
		proc_config->autostart = ft_strequ(val, "true");
	else if (ft_str_starts_with(line, "restart_mode="))
		proc_config->restart_mode = get_restart_mode(val);
	else if (ft_str_starts_with(line, "success_time="))
		proc_config->success_time = get_success_time(val);
	else if (ft_str_starts_with(line, "restart_attempts="))
		proc_config->restart_attempts = ft_atoi(val);
	else if (ft_str_starts_with(line, "sig_graceful_stop="))
		proc_config->sig_graceful_stop = ft_atoi(val);
	else if (ft_str_starts_with(line, "time_before_kill="))
		get_time_before_kill(val, proc_config);
	else if (ft_str_starts_with(line, "umask="))
		proc_config->umask = read_umask(val);
	else
		return FALSE;
	return TRUE;
}

static t_bool		parse_line_for_fileds_(
						t_lst_str *lines,
						t_proc_config *proc_config)
{
	t_str	line;
	char	*semicolon;

	line = LCONT(lines, t_str);
	if (line == NULL || ft_strequ(line, ""))
		return TRUE;
	if ((semicolon = ft_strchr(line, ';')) != NULL)
		*semicolon = '\0';

	if (parse_mallocable_fields_(line, proc_config))
		ft_pass();
	else if (parse_nonmallocable_fields_(line, proc_config))
		ft_pass();
	else
	{
		TASKMAST_ERROR(FALSE, "%s: %s: Invalid field\n",
			proc_config->prog_name, line);
	}

	return FALSE;
}

t_proc_config		load_proc_config(t_lst_str *lines, int *lines_count)
{
	t_proc_config	proc_config;
	t_lst_str		*first_line;

	first_line = lines;
	set_defaults(&proc_config);
	proc_config.prog_name = ft_strdup(ft_strchr(LCONT(lines, t_str), ':') + 1);
	*ft_strrchr(proc_config.prog_name, ']') = '\0';
	LTONEXT(lines);

	for (*lines_count = 0; lines; LTONEXT(lines), (*lines_count)++)
		if (parse_line_for_fileds_(lines, &proc_config))
			break;
	process_default_vals(&proc_config);

	if (lines == NULL)
		lines = ft_lst_get_last(first_line);
	proc_config.hash = get_proc_cfg_hash(lines, *lines_count);
	return proc_config;
}
