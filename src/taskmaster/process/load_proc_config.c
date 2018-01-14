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
	proc_config->autostart = e_never;
	proc_config->restart_attempts = 0;
	proc_config->sig_stop = SIGSTOP;
	proc_config->umask = DEFAULT_UMASK;
}

static t_bool		parse_std_out_err_(t_str line, t_proc_config *proc_config)
{
	if (ft_str_starts_with(line, "stdout="))
	{
		if (proc_config->stdout)
			free(proc_config->stdout);
		proc_config->stdout = ft_strdup(ft_strchr(line, '=') + 1);
	}
	else if (ft_str_starts_with(line, "stderr="))
	{
		if (proc_config->stderr)
			free(proc_config->stderr);
		proc_config->stderr = ft_strdup(ft_strchr(line, '=') + 1);
	}
	else
		return FALSE;
	return TRUE;
}

static t_bool		parse_mallocable_fields_(
						t_str line,
						t_proc_config *proc_config)
{
	if (ft_str_starts_with(line, "command="))
	{
		if (proc_config->launch_cmd)
			free(proc_config->launch_cmd);
		proc_config->launch_cmd = ft_strdup(ft_strchr(line, '=') + 1);
	}
	else if (ft_str_starts_with(line, "expected_exit_codes="))
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
		proc_config->environment = read_config_environ(ft_strchr(line, '='));
	}
	else if (ft_str_starts_with(line, "dir="))
	{
		if (proc_config->dir)
			free(proc_config->dir);
		proc_config->dir = ft_strdup(ft_strchr(line, '=') + 1);
	}
	else
		return FALSE;
	return TRUE;
}

t_proc_config		load_proc_config(t_lst_str *lines, int *lines_count)
{
	t_str			line;
	char			*semicolon;
	t_proc_config	proc_config;
	regex_t			preg;

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

		if (parse_mallocable_fields_(line, &proc_config))
			ft_pass();
		else if (ft_str_starts_with(line, "nprocs="))
			proc_config.nb_of_procs = ft_atoi(ft_strchr(line, '=') + 1);
		else if (ft_str_starts_with(line, "autostart="))
			proc_config.autostart = ft_strequ(ft_strchr(line, '=') + 1, "true");
		else if (ft_str_starts_with(line, "restart_mode="))
			proc_config.restart_mode = get_restart_mode(line);
		else if (ft_str_starts_with(line, "success_time="))
			proc_config.success_time = ft_atoi(ft_strchr(line, '=') + 1);
		else if (ft_str_starts_with(line, "restart_attempts="))
			proc_config.restart_attempts = ft_atoi(ft_strchr(line, '=') + 1);
		else if (ft_str_starts_with(line, "sig_stop="))
			proc_config.sig_stop = ft_atoi(ft_strchr(line, '=') + 1);
		else if (ft_str_starts_with(line, "time_before_kill="))
			proc_config.time_before_kill = ft_atoi(ft_strchr(line, '=') + 1);
		else if (ft_str_starts_with(line, "umask="))
			proc_config.umask = read_umask(ft_strchr(line, '=') + 1);
		else
		{
			TASKMAST_ERROR(FALSE, "%s: %s: Invalid field\n",
				proc_config.prog_name, line);
		}
	}
	process_default_vals_(&proc_config);
	return proc_config;
}
