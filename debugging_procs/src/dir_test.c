#include <stdio.h>
#include <unistd.h>

int		main()
{
	char	buf[248];
	
	printf("Dir_test current dir: %s\n", getcwd(buf, sizeof(buf)));
	return 0;
}