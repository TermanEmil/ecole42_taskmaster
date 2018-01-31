/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_strings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:29 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:29 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shlogic.h"
#include "shell42.h"

void	debug_print_strings(t_str *strings, int top_start)
{
	int		i;

	if (strings == NULL)
		return;

	for (i = 0; strings[i]; i++)
		term_printf(0, top_start + i, "%d) %s", i, strings[i]);
	term_printf(0, top_start + i, "--------");
}
