/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_mini_match.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:26 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:26 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex_tools.h"
#include "libft.h"

/*
** Tell if there is at least one match.
*/

t_bool			regex_mini_match(t_rostr patern, t_rostr str)
{
	regmatch_t	pmatch;

	pmatch = regex_mini_get_regmatch(patern, str);
	return pmatch.rm_so != -1;
}
