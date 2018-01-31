/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_history_construct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:32 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:32 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

t_input_history	input_history_construct(void)
{
	t_input_history	result;

	ft_bzero(&result, sizeof(result));
	result.nb_of_inputs_to_remember = input_history_inputs_to_remember_default;
	result.current_in_index = -1;
	return (result);
}
