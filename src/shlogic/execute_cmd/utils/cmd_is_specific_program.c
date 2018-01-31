/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_specific_program.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:31 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:31 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shlogic.h"

t_bool	cmd_is_specific_program(t_rostr cmd)
{
	if (cmd == NULL)
		return FALSE;
	return cmd[0] != '\0' && ft_strchr("./", cmd[0]) != NULL;
}
