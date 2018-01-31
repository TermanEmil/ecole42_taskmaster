/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_struptime.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:07 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:07 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process42.h"
#include "taskmaster42_utils_.h"

t_rostr	proc_struptime(const t_process *proc)
{
	return str_elapsed_time(proc_uptime(proc));
}
