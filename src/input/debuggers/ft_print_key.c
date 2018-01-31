/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:42 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:42 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_key(char const *str)
{
	while (*str)
	{
		if (ft_isprint(*str))
			ft_printf("%c ", *str);
		else
			ft_printf("%d ", *str);
		str++;
	}
	ft_putnewl();
}
