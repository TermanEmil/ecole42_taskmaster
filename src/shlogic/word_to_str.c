/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:27 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:27 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shlogic.h"

t_str	word_to_str(const t_lst_inkey *keys)
{
	return ft_lst_join(
		(void*)keys,
		(t_rostr (*)(const void*, size_t))&sh_inkey_get_meaning, NULL);
}
