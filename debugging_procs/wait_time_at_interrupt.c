#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int		g_wait_time;

void	sigint_handler(int signum)
{
	(void)signum;
	sleep(g_wait_time);
}

int		main(int argc, char **argv)
{
	g_wait_time = (argv[1]) ? atoi(argv[1]) : 5;
	signal(SIGINT, &sigint_handler);
	sleep(INT_MAX);
	return 0;
}