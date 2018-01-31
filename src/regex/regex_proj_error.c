/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_proj_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:26 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:26 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.h>
#include "ft_errors.h"

void	regex_proj_error(
			const regex_t *regex_patern,
			int errcode,
			int index)
{
	char		err_buf[256];

	regerror(errcode, regex_patern, err_buf, sizeof(err_buf));
	ft_error(TRUE, "%s: regex (%d): %s\n",
		g_proj_name, index, err_buf);
}
