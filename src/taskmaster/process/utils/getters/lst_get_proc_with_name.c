/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_get_proc_with_name.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:08 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:08 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process42.h"

static int	proc_name_cmp_(t_rostr name, t_process *proc)
{
	return ft_strequ(proc->name, name);
}

static int	proc_name_match_(t_rostr name, t_process *proc)
{
	return ft_match(proc->name, name);
}

t_process	*lst_get_proc_with_name(const t_lst_proc* procs, t_rostr name)
{
	t_list	*match;

	match = ft_lst_first(procs, name, ft_strlen(name) + 1,
		(t_lst_cont_cmp*)&proc_name_cmp_);
	return (match == NULL) ? NULL : LCONT(match, t_process*);
}

t_lst_proc	*lst_get_procs_matching_name(const t_lst_proc* procs, t_rostr name)
{
	return ft_lst_filter((t_list*)procs, name, 0,
		(t_lst_cont_cmp*)&proc_name_match_);
}
