#include "libft.h"

void	close_if_open(int *fd)
{
	if (*fd > 0)
	{
		TMP_FAIL_RETRY(close(*fd));
		*fd = -1;
		errno = 0;
	}
}
