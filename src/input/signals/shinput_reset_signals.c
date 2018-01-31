/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shinput_reset_signals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:41 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:41 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

void	shinput_reset_signals(t_shinput * const shinput)
{
	shinput->signaled_sigint = FALSE;
}
