#include "taskmaster42.h"

#define CPY_NOT_NULL_(field) result.field = dup_if_not_null_(cfg->field)

static t_str	dup_if_not_null_(t_rostr str)
{
	if (str == NULL)
		return NULL;

	return ft_strdup(str);
}

static int		expected_exit_codes_tab_len(const int *codes)
{
	int	count;

	count = 0;
	while (*codes != -1)
	{
		count++;
		codes++;
	}
	return count;
}

static int		*cpy_expected_exit_codes_(const int *codes)
{
	int		*result;

	if (codes == NULL)
		return NULL;

	result = ft_memdup(codes, sizeof(int) *
		(expected_exit_codes_tab_len(codes) + 1));
	if (result == NULL)
		ft_err_mem(TRUE);
	return result;
}

static void		cpy_tab_fields_(t_proc_config *dest, const t_proc_config *src)
{
	if (src->expected_exit_statuss)
	{
		dest->expected_exit_statuss =
			cpy_expected_exit_codes_(src->expected_exit_statuss);
	}

	if (src->environment)
	{
		dest->environment = ft_bidimens_dup(src->environment);
		if (dest->environment == NULL)
			ft_err_mem(TRUE);
	}
}

t_proc_config	*proc_config_dup(const t_proc_config *cfg)
{
	t_proc_config	result;
	t_proc_config	*ptr_rs;

	ft_memcpy(&result, cfg, sizeof(result));
	CPY_NOT_NULL_(prog_name);
	CPY_NOT_NULL_(launch_cmd);
	CPY_NOT_NULL_(stdout);
	CPY_NOT_NULL_(stderr);
	CPY_NOT_NULL_(dir);
	cpy_tab_fields_(&result, cfg);

	ptr_rs = ft_memdup(&result, sizeof(result));
	if (ptr_rs == NULL)
		ft_err_mem(TRUE);
	return ptr_rs;
}
