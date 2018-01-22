#include <stdio.h>
#include <stdlib.h>

int		main()
{
	const char	*val;

	val = getenv("PATH");
	printf("PATH = %s\n", val);
	return 0;
}