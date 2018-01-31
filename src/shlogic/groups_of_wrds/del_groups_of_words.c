/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_groups_of_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:34 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:34 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shlogic.h"

/*
** Delete the given groups of words (only the group and [word structure]~).
*/

void	del_groups_of_words(t_grps_wrds *groups_of_words)
{
	t_grps_wrds	*group;
	t_lst_words	*words;

	for (group = groups_of_words; group; LTONEXT(group))
	{
		words = LCONT(group, t_lst_words*);
		ft_lstdel(&words, NULL);
	}
	ft_lstdel(&groups_of_words, NULL);
}
