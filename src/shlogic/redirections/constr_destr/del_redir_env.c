/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_redir_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:22 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:22 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_redirs_.h"

void		del_redir_env(t_redir_env *redir_env)
{
	ft_memdel((void**)&redir_env->redir_type);
	ft_memdel((void**)&redir_env->next_word_str);
}
