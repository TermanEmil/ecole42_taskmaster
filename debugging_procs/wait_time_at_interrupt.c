#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void	write_to_file(const char *str)
{
	printf("SIGINT %d\n", getpid());
	// int		fd = open("./aux/log1", O_WRONLY | O_APPEND);
	// char	buf[124];

	// sprintf(buf, "%s %d\n", str, getpid());
	// write(fd, buf, strlen(buf));
	// close(fd);
}

void	sigint_handler(int signum)
{
	(void)signum;
	// write_to_file("SIGINT");
	printf("SIGINT %d\n", getpid());
}

int		main(int argc, char **argv)
{
	printf("started %d\n", getpid());
	int	wait_time;

	wait_time = (argv[1]) ? atoi(argv[1]) : 5;
	signal(SIGINT, &sigint_handler);

	// Wait for any signal.
	pause();
	sleep(wait_time);
	return 0;
}