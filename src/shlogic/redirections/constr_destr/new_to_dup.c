/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_to_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:22 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:22 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_redirs_.h"

t_to_dup	new_to_dup(int fd, int default_fd, t_bool to_close)
{
	t_to_dup	result;

	result.fd = fd;
	result.default_fd = default_fd;
	result.to_close = to_close;
	return result;
}
