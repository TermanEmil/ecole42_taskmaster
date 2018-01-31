/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:55:25 by eterman           #+#    #+#             */
/*   Updated: 2018/01/31 19:55:25 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "taskmaster42.h"
#include <sys/wait.h>

t_shdata			g_shdata;
t_shinput			*g_shinput;
t_current_input		*g_current_in;
t_taskmast			g_taskmast;
pthread_mutex_t		g_printf_mutex;

static int	print_help_()
{
	ft_printf("help:\ntaskmaster <config_file>\n");
	return 0;
}

static void	start_listening_to_signals_()
{
	listen_to_signals();
	g_taskmast.signal_flags.signals[SIGCHLD] = TRUE;
	taskmast_parse_signals();
}

int			main(int argc, const char **argv, const char **envp)
{
	if (argc < 2 || ft_strequ(argv[1], "-h"))
		return print_help_();

	ft_printf("Pid: %d\n", getpid());
	pthread_mutex_init(&g_printf_mutex, NULL);
	init_shell(envp);

	term_restore_to_old_term_data();
	init_taskmaster(argv[1]);
	taskmast_start(&g_taskmast);
	term_enable_raw_mode(term_get_data());

	start_listening_to_signals_();

	if (g_shdata.is_term)
	{
		term_putnewl();
		input_reprint_here(g_current_in);
	}

	while (1)
	{
		while (!g_taskmast.signal_flags.its_safe)
			usleep(1000);
		input_reprint_here(g_current_in);

		shinput_reset_signals(g_shinput);
		shell_read_user_input();
		shinput_process_signals(g_shinput);
	}

	event_exit(0);
}
