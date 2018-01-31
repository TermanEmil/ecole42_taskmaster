/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceess_tilde.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:16 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:16 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shlogic.h"

/*
** Substitute tilda.
*/

void	proceess_tilde(t_lst_words	*words, const t_shvars *shvars)
{
	t_lst_inkey	*processed_word;
	t_lst_inkey	*word;

	for (; words; LTONEXT(words))
	{
		if (words->content == NULL)
			continue;

		word = LCONT(words, t_lst_inkey*);
		processed_word = process_tilde_in_word(word, shvars);
		words->content = processed_word;
		ft_lstdel(&word, (t_ldel_func*)&sh_inkey_destruct);
	}
}
