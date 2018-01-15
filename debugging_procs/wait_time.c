#include <unistd.h>
#include <stdlib.h>

int		main(int argc, char **argv)
{
	if (argc == 1)
		sleep(5);
	else
		sleep(atoi(argv[1]));
	return 0;
}