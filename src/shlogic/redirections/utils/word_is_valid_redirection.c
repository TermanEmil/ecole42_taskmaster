/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_is_valid_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:20 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:20 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_redirs_.h"

t_bool	word_is_valid_redirection(const t_lst_inkey* in_keys)
{
	t_str	tmp;
	t_bool	condition;

	tmp = word_to_str(in_keys);
	if (tmp == NULL)
		ft_err_mem(TRUE);
	condition = ft_strnchr(tmp, "><") && !ft_strnchr(tmp, "\"\'\\`()[]{}");	
	free(tmp);
	return condition;
}
