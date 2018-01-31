#include "taskmaster42.h"

int		proc_mv_to_dir(t_rostr dir)
{
	if (dir)
		if (chdir(dir) == -1)
		{
			TASKMAST_ERROR(FALSE, "%s: %s.\n", dir, strerror(errno));
			return -1;
		}
	return 0;
}
