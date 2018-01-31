/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:32 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:32 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shlogic.h"

void	dup_and_close(int fd, int default_fd, t_bool close_it)
{
	if (fd != default_fd)
	{
		if (TMP_FAIL_RETRY(dup2(fd, default_fd)) == -1)
			ft_err_erno(errno, TRUE);
		if (close_it &&
			fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
		{
			TMP_FAIL_RETRY(close(fd));
			errno = 0;
		}
	}
}
