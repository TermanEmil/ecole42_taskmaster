#include <stdio.h>
#include <stdlib.h>

int		main(int argc, const char **argv, const char **envp)
{
	int		i;

	for (i = 0; envp[i]; i++)
		printf("%s\n", envp[i]);
	return 0;
}