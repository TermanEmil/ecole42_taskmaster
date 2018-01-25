#include "config_reader_.h"
#include <signal.h>
#include "shell42.h"
#include "regex_tools.h"

static void			process_default_vals_(t_proc_config *proc_config)
{
	if (proc_config->launch_cmd == NULL)
	{
		TASKMAST_ERROR(FALSE, "process %s: No command specified\n",
			proc_config->prog_name);
	}
}

static void			set_defaults_(t_proc_config *proc_config)
{
	ft_bzero(proc_config, sizeof(*proc_config));
	proc_config->nb_of_procs = 1;
	proc_config->autostart = TRUE;
	proc_config->restart_attempts = 0;
	proc_config->sig_graceful_stop = SIGINT;
	proc_config->umask = DEFAULT_UMASK;
	proc_config->restart_attempts = 1;
	proc_config->restart_mode = e_never;
	proc_config->time_before_forced_kill = 1;
	proc_config->success_time = -1;
}

static void			get_time_before_kill(t_str val, t_proc_config *proc_config)
{
	int		value;

	value = ft_atoi(val);
	if (value < 0)
	{
		TASKMAST_ERROR(FALSE, "time_before_kill = %d: can't be negative. "
			"It will be ignored\n", value);
		proc_config->time_before_forced_kill = -1;
	}
	else
		proc_config->time_before_forced_kill = value;
}

static t_bool		parse_std_out_err_(t_str line, t_proc_config *proc_config)
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

static t_bool		parse_mallocable_fields_(
						t_str line,
						t_proc_config *proc_config)
{
	t_str	val;

	val = ft_strchr(line, '=') + 1;
	if (ft_str_starts_with(line, "command="))
	{
		if (proc_config->launch_cmd)
			free(proc_config->launch_cmd);
		proc_config->launch_cmd = ft_strdup(val);
	}
	else if (ft_str_starts_with(line, "expected_exit_status="))
	{
		if (proc_config->expected_exit_codes)
			free(proc_config->expected_exit_codes);
		proc_config->expected_exit_codes = get_expected_exit_codes(line);
	}
	else if (parse_std_out_err_(line, proc_config))
		ft_pass();
	else if (ft_str_starts_with(line, "environment="))
	{
		if (proc_config->environment)
			ft_free_bidimens(proc_config->environment);
		proc_config->environment = read_config_environ(val);
	}
	else if (ft_str_starts_with(line, "dir="))
	{
		if (proc_config->dir)
			free(proc_config->dir);
		proc_config->dir = ft_strdup(val);
	}
	else
		return FALSE;
	return TRUE;
}

static size_t		get_proc_cfg_hash(t_lst_str *lines, int lines_count)
{
	size_t	hash;

	hash = 0;
	for (; lines && lines_count >= -1; LTOPREV(lines), lines_count--)
	{
		if (ft_strequ(LSTR(lines), ""))
			continue;
		hash ^= ft_hash(lines->content, lines->content_size);
	}
	return hash;
}

static int			get_success_time_(t_rostr val)
{
	int		intval;

	intval = ft_atoi(val);
	if (intval < 0)
	{
		TASKMAST_ERROR(FALSE, "Success time = %d can't be negative.\n", intval);
		return -1;
	}
	else
		return intval;
}

t_proc_config		load_proc_config(t_lst_str *lines, int *lines_count)
{
	t_str			line;
	char			*semicolon;
	t_proc_config	proc_config;
	regex_t			preg;
	t_lst_str		*first_line;
	t_str			val;

	first_line = lines;
	set_defaults_(&proc_config);
	proc_config.prog_name = ft_strdup(ft_strchr(LCONT(lines, t_str), ':') + 1);
	*ft_strchr(proc_config.prog_name, ']') = '\0';
	LTONEXT(lines);

	for (*lines_count = 0; lines; LTONEXT(lines), (*lines_count)++)
	{
		line = LCONT(lines, t_str);
		if (ft_strequ(line, ""))
			break;
		if ((semicolon = ft_strchr(line, ';')) != NULL)
			*semicolon = '\0';

		val = ft_strchr(line, '=') + 1;
		if (parse_mallocable_fields_(line, &proc_config))
			ft_pass();
		else if (ft_str_starts_with(line, "nprocs="))
			proc_config.nb_of_procs = ft_atoi(val);
		else if (ft_str_starts_with(line, "autostart="))
			proc_config.autostart = ft_strequ(val, "true");
		else if (ft_str_starts_with(line, "restart_mode="))
			proc_config.restart_mode = get_restart_mode(val);
		else if (ft_str_starts_with(line, "success_time="))
			proc_config.success_time = get_success_time_(val);
		else if (ft_str_starts_with(line, "restart_attempts="))
			proc_config.restart_attempts = ft_atoi(val);
		else if (ft_str_starts_with(line, "sig_graceful_stop="))
			proc_config.sig_graceful_stop = ft_atoi(val);
		else if (ft_str_starts_with(line, "time_before_kill="))
			get_time_before_kill(val, &proc_config);
		else if (ft_str_starts_with(line, "umask="))
			proc_config.umask = read_umask(val);
		else
		{
			TASKMAST_ERROR(FALSE, "%s: %s: Invalid field\n",
				proc_config.prog_name, line);
		}
	}
	process_default_vals_(&proc_config);

	if (lines == NULL)
		lines = ft_lst_get_last(first_line);
	proc_config.hash = get_proc_cfg_hash(lines, *lines_count);
	return proc_config;
}
