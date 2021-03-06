/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_cmd_arrow_right.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:43 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:43 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int		key_cmd_arrow_right(void)
{
	int		x;
	int		y;
	int		const width = term_get_width();

	shell_get_cursor_pos(&x, &y);
	if (x >= width - 1 && y >= term_get_height() - 1)
		return (-1);
	if (current_input_mv_cursor_pos(1) == 0)
	{
		if (x >= width - 1)
		{
			INTERPT_RETRY(term_cursor_goto(0, y + 1));
		}
		else
			INTERPT_RETRY(term_cursor_goto(x + 1, y));
	}
	g_current_in->cursor_pos--;
	input_reprint(g_current_in);
	g_current_in->cursor_pos++;
	return (0);
}
