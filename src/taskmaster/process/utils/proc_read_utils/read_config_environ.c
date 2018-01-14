#include "config_reader_.h"

t_str	*read_config_environ(t_str line)
{
	t_str		*fields;
	int			i;

	fields = ft_strsplit(ft_strchr(line, '=') + 1, ',');
	for (i = 0; fields[i]; i++)
		if (ft_strchr(fields[i], '=') == NULL)
		{
			ft_prerror(FALSE, "environment: Invalid environment format: %s\n",
				fields[i]);
			ft_free_bidimens(fields);
			return NULL;
		}
	return fields;
}