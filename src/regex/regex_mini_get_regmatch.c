/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_mini_get_regmatch.c                          :+:      :+:    :+:   */
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
** Extract the first match.
*/

regmatch_t		regex_mini_get_regmatch(t_rostr patern, t_rostr str)
{
	regex_t		regex_patern;
	regmatch_t	pmatch;
	int			ret;

	if ((ret = regcomp(&regex_patern, patern, REG_EXTENDED)) != 0)
		regex_proj_error(&regex_patern, ret, 1);
	ret = regexec(&regex_patern, str, 1, &pmatch, 0);

	if (ret == REG_NOMATCH)
	{
		pmatch.rm_so = -1;
		pmatch.rm_eo = -1;
	}
	else if (ret != 0)
		regex_proj_error(&regex_patern, ret, 42);

	regfree(&regex_patern);
	return pmatch;
}
