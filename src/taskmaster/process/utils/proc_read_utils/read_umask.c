/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_umask.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:04 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:04 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config_reader_.h"

mode_t		read_umask(t_str umask_strval)
{
	return ft_atoi_base(umask_strval, 8);
}
