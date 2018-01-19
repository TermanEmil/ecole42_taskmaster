#ifndef _CONFIG_READER__H_
# define _CONFIG_READER__H_

# include "taskmaster42.h"
# include "ft_errors.h"
# include "shellvars.h"

# include <regex.h>
# include <sys/types.h>

# define DEFAULT_UMASK 0022

void			set_env_vars_to_str(const t_shvars *shvars, const regex_t *preg,
					t_str *str_ptr);
void			set_env_vars_to_cfg_file(const t_shvars *shvars,
					t_lst_str *config_file_lines);

t_proc_config	load_proc_config(t_lst_str *lines, int *lines_count);
t_restart_mode	get_restart_mode(t_str val);
int				*get_expected_exit_codes(t_str val);
t_str			*read_config_environ(t_str val);
mode_t			read_umask(t_str umask_strval);

#endif