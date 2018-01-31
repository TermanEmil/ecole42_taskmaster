/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:29 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:29 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shlogic.h"

int				execute_cmd_env(t_cmd_env *cmd_env)
{
	t_str	*env_tab;
	int		i;

	env_tab = shvars_form_key_val_tab(cmd_env->shvars->env);
	for (i = 0; env_tab[i]; i++)
		ft_putendl(env_tab[i]);
	ft_free_bidimens(env_tab);
	return 0;
}
