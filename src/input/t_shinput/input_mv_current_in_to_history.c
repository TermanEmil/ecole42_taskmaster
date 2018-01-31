/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mv_current_in_to_history.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:48 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:48 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

void			input_mv_current_in_to_history(t_shinput * const input)
{
	input_history_add_seq(&input->history, *input->current.input);
	current_in_resset(&input->current, FALSE);
}
