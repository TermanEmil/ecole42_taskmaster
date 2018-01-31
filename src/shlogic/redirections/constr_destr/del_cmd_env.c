/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_cmd_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:22 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:22 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_redirs_.h"

void	del_cmd_env(t_cmd_env *cmd_env)
{
	ft_free_bidimens(cmd_env->argv);
	ft_lstdel(&cmd_env->fd_io.other, &std_mem_del);
	free(cmd_env);
}
