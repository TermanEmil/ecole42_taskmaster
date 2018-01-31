/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_process_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:09 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:09 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"

t_str	new_process_name(t_rostr default_name, int name_id)
{
	char	buf[16];

	ft_bufitoa(name_id, buf);
	return ft_strmegajoin(3, default_name, "_", buf);
}
