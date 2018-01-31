/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_expected_exit_status.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:56:03 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:56:03 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The tab is a -1 ended array.
*/

t_bool		is_expected_exit_status(int code, const int *expected_exit_codes)
{
	if (expected_exit_codes == NULL || *expected_exit_codes == -1)
		return code == EXIT_SUCCESS;
	else
	{
		for (; *expected_exit_codes != -1; expected_exit_codes++)
			if (*expected_exit_codes == code)
				return TRUE;
	}
	return FALSE;
}
