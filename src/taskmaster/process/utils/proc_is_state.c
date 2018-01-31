/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_is_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:09 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:09 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process42.h"

/*
** List util.
*/

t_bool	proc_is_state(enum e_proc_state *state, const t_process *proc)
{
	return ISSTATE(proc, *state);
}
