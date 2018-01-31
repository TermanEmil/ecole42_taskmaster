/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_if_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:14 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:14 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
