#include "regex_tools.h"
#include "config_reader_.h"

/*
** Substititues enviroment or local vars variables.
** If %(program_name)s is found, it is left like this.
*/

void			set_env_vars_to_cfg_file(
					const t_shvars *shvars,
					t_lst_str *config_file_lines)
{
	regex_t	preg;
	int		ret;
	char	*comma;

	if ((ret = regcomp(&preg, "%\\([a-zA-Z0-9_]+\\)s", REG_EXTENDED)) != 0)
		regex_proj_error(&preg, ret, 32);
	
	for (; config_file_lines; LTONEXT(config_file_lines))
	{
		comma = ft_strchr(LCONT(config_file_lines, t_str), ';');
		if (comma)
			*comma = '\0';
		set_env_vars_to_str(
			shvars, &preg, (t_str*)&config_file_lines->content);
	}

	regfree(&preg);
}
