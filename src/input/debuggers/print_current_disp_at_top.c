/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_current_disp_at_top.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:42 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:42 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

void	print_current_disp_at_top(void)
{
	char	* const disp_total = input_seq_get_displayed(
		g_current_in->input, 0);

	int x, y;

	shell_get_cursor_pos(&x, &y);
	term_cursor_goto(0, 0);
	term_clear_from_cursor_to_end_line();
	ft_printf("current :%s:\n", disp_total);
	term_move_cursor_to_left_most();
	ft_printf("pos: %d; len: %d", g_current_in->cursor_pos,
		g_current_in->input->count);
	free(disp_total);
	term_cursor_goto(x, y);
}
