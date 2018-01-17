#include "taskmaster42.h"
#include "taskmaster42_utils_.h"
#include <fcntl.h>

#define WR_CR_TR_ O_WRONLY | O_CREAT | O_TRUNC

void	taskmast_setup_logger(t_taskmast *taskmast)
{
	int		fd;

	close_if_open(&taskmast->logger.log_file_fd);
	if (taskmast->logger.log_file_path)
	{
		fd = open(taskmast->logger.log_file_path, WR_CR_TR_, 0644);
		if (fd == -1)
		{
			TASKMAST_ERROR(FALSE, "%s: %s\n",
				taskmast->logger.log_file_path, strerror(errno));
			errno = 0;
		}
		else
			taskmast->logger.log_file_fd = fd;
	}
}
