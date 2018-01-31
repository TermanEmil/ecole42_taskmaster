/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_cmd_arrow_down.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:47 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:47 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int		key_cmd_arrow_down(void)
{
	history_change_seq_at(&g_shinput->history, g_current_in->input,
		g_shinput->history.current_in_index);

	history_set_current_in(&g_shinput->history, g_current_in,
		g_shinput->history.current_in_index - 1);
	
	return (0);
}
