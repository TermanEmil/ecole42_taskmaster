#include "ft_errors.h"
#include "taskmaster42.h"
#include "regex_tools.h"
#include "config_reader_.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void	load_defaults_(t_taskmast *taskmast)
{
	taskmast->logger.log_to_term = FALSE;
	taskmast->logger.log_is_on = TRUE;
}

static t_lst_str	*read_config_(t_rostr file_path)
{
	int			fd;
	int			ret;
	t_str		line;
	t_lst_str	*file_lines;

	if ((fd = open(file_path, O_RDONLY)) == -1)
	{
		TASKMAST_ERROR(FALSE,
			"%s: %s: %s\n", g_proj_name, file_path, strerror(errno));
		return NULL;
	}
	file_lines = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
		ft_lstadd(&file_lines, ft_lstnew_str_nocpy(line));

	if (ret < 0)
	{
		if (ret == -1)
			ft_err_mem(TRUE);
		else
			TASKMAST_ERROR(TRUE, "%s\n", strerror(errno));
	}

	close(fd);
	return file_lines;
}

static void			load_program_cfg_(
						t_taskmast *taskmast,
						t_lst_str *file_lines,
						int *lines_count)
{
	t_proc_config	proc_cfg;

	proc_cfg = load_proc_config(file_lines, lines_count);
	ft_lstadd(&taskmast->proc_cfgs,
		ft_lstnew(&proc_cfg, sizeof(proc_cfg)));
}

static void			load_from_lines_(
						t_taskmast *taskmast,
						t_lst_str *file_lines)
{
	t_rostr			line;
	int				lines_count;

	ft_bzero(taskmast, sizeof(*taskmast));
	load_defaults_(taskmast);
	for (; file_lines; LTONEXT(file_lines))
	{
		line = LCONT(file_lines, t_rostr);
		lines_count = -1;
		if (ft_strequ(line, "[taskmaster]"))
			lines_count = load_taskmaster_config(taskmast, file_lines->next);
		else if (regex_mini_match("^\\[program:.*\\]$", line))
			load_program_cfg_(taskmast, file_lines, &lines_count);
		else if (ft_strequ(line, ""))
			ft_pass();
		else
			TASKMAST_ERROR(FALSE, "%s: Invalid field\n", line);
		if (lines_count != -1)
			file_lines = ft_lstget(file_lines, lines_count);
	}
}

int		taskmast_load_all_config(
			const t_shvars *shvars,
			t_taskmast *taskmast,
			t_rostr file_path)
{
	t_lst_str	*file_lines;

	file_lines = read_config_(file_path);
	set_env_vars_to_cfg_file(shvars, file_lines);
	load_from_lines_(taskmast, file_lines);
	ft_lstdel(&file_lines, &std_mem_del);
	return 0;
}
