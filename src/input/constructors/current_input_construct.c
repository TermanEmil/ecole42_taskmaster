/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_input_construct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:32 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:32 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

t_current_input	current_input_construct(void)
{
	t_current_input	result;
	t_shinput_seq	seq;

	ft_bzero(&result, sizeof(result));
	seq = shinput_seq_construct();
	result.input = ft_memdup(&seq, sizeof(seq));
	return (result);
}
