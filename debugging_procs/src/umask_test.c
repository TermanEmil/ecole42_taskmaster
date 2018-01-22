#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILE_NAME "./umask_test_new_file"

int		main(int argc, const char **argv)
{
	int			fd;
	struct stat	stat_result;

	fd = open(FILE_NAME, O_CREAT, 0777);
	if (fd == -1)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}

	close(fd);

	if (stat(FILE_NAME, &stat_result) == -1)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);	
	}

	printf("permissions: %o\n", stat_result.st_mode);

	if (argc == 1)
	{
		if (unlink(FILE_NAME) != 0)
		{
			perror(strerror(errno));
			exit(EXIT_FAILURE);	
		}
	}
	return 0;
}