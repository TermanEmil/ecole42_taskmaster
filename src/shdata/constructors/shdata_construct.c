/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shdata_construct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:16 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:16 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

t_shdata	shdata_construct(void)
{
	t_shdata	result;

	ft_bzero(&result, sizeof(result));
	result.input = shinput_construct();
	result.running_a_process = FALSE;
	return (result);
}
