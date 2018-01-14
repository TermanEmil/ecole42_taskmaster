#include "libft.h"

/*
**  999:99:99
*/

t_rostr	str_elapsed_time(int elapsed_time)
{
	static char		buf[10];
	int				hours;
	int				mins;
	int				secs;

	hours = elapsed_time / (60 * 60);
	elapsed_time = elapsed_time % (60 * 60);
	mins = elapsed_time / 60;
	elapsed_time = elapsed_time % 60;
	secs = elapsed_time;
	ft_sprintf(buf, "%0d:%0d:%0d", hours, mins, secs);
	return buf;
}
