#include "config_reader_.h"
#include "regex_tools.h"

static int	count_numbers_in_strarray_(t_str array_str)
{
	int		count;
	char	*comma;

	if (ft_strequ(array_str, "[]"))
		return 0;
	count = 1;
	while (*array_str)
	{
		comma = ft_strchr(array_str, ',');
		if (comma == NULL)
			break;
		else
		{
			array_str = comma + 1;
			count++;
		}
	}
	return count;
}

static void		process_valid_exit_code_(int exit_code)
{
	if (exit_code < 0 || exit_code > 255)
	{
		ft_error(FALSE, "%s: expected_exit_codes: %d invalid exit code\n",
			g_proj_name, exit_code);
	}
}

static int	*read_array_(t_str array_str)
{
	int		*result;
	int		i;
	char	*comma;

	result = malloc(sizeof(int) * (count_numbers_in_strarray_(array_str) + 1));
	if (ft_strequ(array_str, "[]"))
	{
		result[0] = -1;
		return result;
	}
	result[0] = ft_atoi(array_str + 1);
	process_valid_exit_code_(result[0]);
	for (i = 0; *array_str; i++)
	{
		comma = ft_strchr(array_str, ',');
		if (comma == NULL)
			break;
		array_str = comma + 1;
		result[i] = ft_atoi(comma + 2);
		process_valid_exit_code_(result[i]);
	}
	result[i] = -1;
	return result;
}

int			*get_expected_exit_codes(t_str line)
{
	t_str	val;

	val = ft_strchr(line, '=') + 1;
	if (!regex_mini_match("(\\[([0-9]+, )*[0-9]\\]|\\[\\])", val))
	{
		ft_error(FALSE, "%s: Invalid array format: %s\n",
			g_proj_name, val);
		return NULL;
	}
	return read_array_(val);
}
