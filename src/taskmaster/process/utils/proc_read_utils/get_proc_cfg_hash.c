/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_proc_cfg_hash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:04 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:04 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config_reader_.h"

size_t		get_proc_cfg_hash(t_lst_str *lines, int lines_count)
{
	size_t	hash;

	hash = 0;
	for (; lines && lines_count >= -1; LTOPREV(lines), lines_count--)
	{
		if (ft_strequ(LSTR(lines), ""))
			continue;
		if (lines->content)
			hash ^= ft_hash(lines->content, ft_strlen(lines->content));
	}
	return hash;
}
