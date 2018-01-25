#include "shell42.h"
#include "taskmaster42.h"

t_shdata		g_shdata;
t_shinput		*g_shinput;
t_current_input	*g_current_in;
t_taskmast		g_taskmast;

static int	print_help_()
{
	ft_printf("help:\ntaskmaster <config_file>\n");
	return 0;
}

int		main(int argc, const char **argv, const char **envp)
{
	if (argc < 2 || ft_strequ(argv[1], "-h"))
		return print_help_();

	init_shell(envp);

	term_restore_to_old_term_data();
	init_taskmaster(argv[1]);
	taskmast_start(&g_taskmast);
	term_enable_raw_mode(term_get_data());  

	if (g_shdata.is_term)
	{
		term_putnewl();
		input_reprint_here(g_current_in);
	}

	while (1)
	{
		shinput_reset_signals(g_shinput);
		shell_read_user_input();
		shinput_process_signals(g_shinput);
	}

	event_exit(0);
}
