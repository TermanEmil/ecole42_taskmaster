#include "taskmaster42.h"
#include "libft.h"
#include <fcntl.h>

int	process_std_redir_to_file(t_rostr std_fd_val, int default_fd)
{
	int		fd;

	if (std_fd_val == NULL)
		return 0;

	fd = open(std_fd_val, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
	{
		TASKMAST_ERROR(FALSE, "%s: %s\n", std_fd_val, strerror(errno));
		TMP_FAIL_RETRY(close (default_fd));
		errno = 0;
		return -1;
	}
	if (TMP_FAIL_RETRY(dup2(fd, default_fd) == -1))
	{
		TASKMAST_ERROR(FALSE, "dup2: %s\n", strerror(errno));
		return -1;
	}	
	TMP_FAIL_RETRY(close(fd));
	return 0;
}