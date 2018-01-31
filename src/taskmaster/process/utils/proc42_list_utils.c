/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc42_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:10 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:10 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process42.h"

t_bool	proc_cfg_hash_equ(const size_t *hash, const t_proc_config *config)
{
	return *hash == config->hash;
}

t_bool	proc_ref_equ(const t_process *proc1, const t_process *proc2)
{
	return proc1 == proc2;
}
