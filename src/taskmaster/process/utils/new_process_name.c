#include "taskmaster42.h"

t_str	new_process_name(t_rostr default_name, int name_id)
{
	char	buf[16];

	ft_bufitoa(name_id, buf);
	return ft_strmegajoin(3, default_name, "_", buf);
}
