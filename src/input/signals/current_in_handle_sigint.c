/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_in_handle_sigint.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:40 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:40 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

void	current_in_handle_sigint(t_shinput * const shinput)
{
	if (!shinput->signaled_sigint)
		return;

	IF_TERM(ft_putstr("^C"));

	current_in_resset(&shinput->current, TRUE);
	shinput->current.line_index = 0;

	shinput_seq_destruct(shinput->history.tmp_current_in);
	shinput->history.tmp_current_in = NULL;
	shinput->history.current_in_index = -1;

	ft_strcpy(g_shdata.prompt, DEFAULT_PROMPT);

	if (g_shdata.is_term)
	{
		term_putnewl();
		input_reprint_here(&shinput->current);
	}
	else
		event_exit(0);
	ft_lstdel(&g_shdata.started_procs, &std_mem_del);
}
