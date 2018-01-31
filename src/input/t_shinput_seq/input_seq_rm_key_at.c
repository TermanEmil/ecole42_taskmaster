/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_seq_rm_key_at.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:36 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:36 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"
#include "ft_colors.h"

void	input_seq_rm_key_at(t_shinput_seq * const seq, size_t const index)
{
	if (index >= seq->count)
	{
		// ft_err(C_CYAN "Warning in input_seq_rm_key_at: "
			// "index out of range" C_EOC);
	}
	if (ft_lstrm_at(&seq->keys, index, (t_ldel_func*)&sh_inkey_destruct) == 0)
		seq->count--;
}
