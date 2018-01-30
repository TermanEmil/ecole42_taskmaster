#include "config_reader_.h"
#include "regex_tools.h"

t_str	*read_config_environ(t_str val)
{
	t_str		*fields;
	int			i;
	int			ret;
	regex_t		preg;


	fields = ft_strsplit(val, ',');
	if ((ret = regcomp(&preg, "^[a-zA-Z0-9_]+=.*$", REG_EXTENDED)) != 0)
		regex_proj_error(&preg, ret, 0);

	for (i = 0; fields[i]; i++)
	{
		ret = regexec(&preg, fields[i], 0, NULL, 0);  
		if (ret == REG_NOMATCH)
		{
			TASKMAST_ERROR(FALSE, "environment: Invalid format: %s\n",
				fields[i]);
			ft_free_bidimens(fields);
			fields = NULL;
			break;
		}
		else if (ret != 0)
			regex_proj_error(&preg, ret, 1);
	}
	regfree(&preg);
	return fields;
}
