/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskmast_reset_signals.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:55 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:55 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster42.h"

void	taskmast_reset_signals()
{
	ft_bzero(&g_taskmast.signal_flags, sizeof(g_taskmast.signal_flags));
	g_taskmast.signal_flags.its_safe = TRUE;
}
