/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shinput_process_signals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:40 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:40 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shinput.h"

void	shinput_process_signals(t_shinput * const shinput)
{
	current_in_handle_sigint(shinput);
}
