#include "config_reader_.h"
#include "regex_tools.h"

t_str	*read_config_environ(t_str val)
{
	t_str		*fields;
	int			i;

	fields = ft_strsplit(val, ',');
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
