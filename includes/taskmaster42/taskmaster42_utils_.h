#ifndef _TASKMASTER42_UTILS__H_
# define _TASKMASTER42_UTILS__H_

# include "libft.h"

void		close_if_open(int *fd);
int			dup2_close(int fd, int default_fd);
t_rostr		str_elapsed_time(int elapsed_time);

#endif