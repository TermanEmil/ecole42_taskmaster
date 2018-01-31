/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shinput_construct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:31 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:31 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

t_shinput	shinput_construct(void)
{
	t_shinput	result;

	result.current = current_input_construct();
	result.history = input_history_construct();
	return (result);
}
