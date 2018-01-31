/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskmast_log.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:53 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:53 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "taskmaster42.h"

void	taskmast_log(const char *format, ...)
{
	va_list		ap;
	t_data		*data;

	if (g_taskmast.logger.log_file_fd <= 0 || !g_taskmast.logger.log_is_on)
		return;

	pthread_mutex_lock(&g_printf_mutex);
	data = sprintf_new_data();
	va_start(ap, format);
	process_format(format, &ap, data);
	va_end(ap);
	if (data->str)
	{
		write(g_taskmast.logger.log_file_fd, data->str, data->printed_chars);
		free(data->str);
	}
	free(data);
	pthread_mutex_unlock(&g_printf_mutex);
}
