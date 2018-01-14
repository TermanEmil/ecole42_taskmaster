#include "taskmaster42.h"

int		dup2_close(int fd, int default_fd)
{
	if (fd > 0)
	{
		if (TMP_FAIL_RETRY(dup2(fd, default_fd)) == -1)
		{
			TASKMAST_ERROR(FALSE, "dup2: fd: %d: %s\n", fd, strerror(errno));
			errno = 0;
			return -1;
		}
		else
			TMP_FAIL_RETRY(close(fd));
	}
	errno = 0;
	return 0;
}
