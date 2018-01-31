/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_seq_insert_seq.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:38 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:38 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

void	input_seq_insert_seq(t_shinput_seq * const seq, size_t const index,
			t_shinput_seq * const to_insert)
{
	if (ft_lst_insert_range(&seq->keys, index, to_insert->keys) == 0)
		seq->count += to_insert->count;
}
