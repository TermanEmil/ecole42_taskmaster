#include "regex_tools.h"
#include "config_reader_.h"

static int		extract_and_subs_env_val_(
					t_str *str,
					const t_shvars *shvars,
					const regmatch_t *pmatch)
{
	t_rostr		env_val;
	t_str		env_key;
	int			key_match_len;
	t_str		tmp;

	key_match_len = pmatch->rm_eo - pmatch->rm_so - 4;
	env_key = ft_strndup(*str + pmatch->rm_so + 2, key_match_len);
	if (ft_strequ(env_key, "program_name"))
	{
		free(env_key);
		return 1;
	}
	else
		env_val = get_shvar(env_key, shvars);
	free(env_key);
	if (env_val == NULL)
		env_val = "";
	ft_str_mlc_sub(str, env_val, pmatch->rm_so, pmatch->rm_eo);
	return ft_strlen(env_val);
}

void			set_env_vars_to_str(
					const t_shvars *shvars,
					const regex_t *preg,
					t_str *str_ptr)
{
	regmatch_t	pmatch;
	int			ret;
	t_str		str;
	t_str		tmp;
	int			delta;

	str = *str_ptr;
	ret = REG_NOMATCH;
	while (*str && (ret = regexec(preg, str, 1, &pmatch, 0)) == 0)
	{
		pmatch.rm_eo += str - *str_ptr;
		pmatch.rm_so += str - *str_ptr;
		delta = extract_and_subs_env_val_(str_ptr, shvars, &pmatch);
		str += pmatch.rm_so - (str - *str_ptr) + delta;
	}
	if (ret != REG_NOMATCH && ret != 0)
		regex_proj_error(preg, ret, 33);
}
