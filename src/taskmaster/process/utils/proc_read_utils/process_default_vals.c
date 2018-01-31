/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_default_vals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:05 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:05 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config_reader_.h"

void			process_default_vals(t_proc_config *proc_config)
{
	if (proc_config->launch_cmd == NULL)
	{
		TASKMAST_ERROR(FALSE, "process %s: No command specified\n",
			proc_config->prog_name);
	}
}
