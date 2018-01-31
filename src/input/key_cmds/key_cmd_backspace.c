/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_cmd_backspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:46 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:46 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int		key_cmd_backspace(void)
{
	if (g_current_in->cursor_pos <= 0)
		return (-1);
	if (key_cmd_arrow_left() != 0)
		return (-1);

	input_seq_rm_key_at(g_current_in->input, g_current_in->cursor_pos);
	term_del_char();
	
	g_current_in->cursor_pos--;
	input_reprint(g_current_in);
	g_current_in->cursor_pos++;
	return (0);
}
