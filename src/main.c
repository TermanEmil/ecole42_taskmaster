#include "shell42.h"
#include "taskmaster42.h"
#include "regex_tools.h"
#include "ft_colors.h"
#include "taskmaster42_utils_.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <wait.h>
#include <pthread.h>

t_shdata		g_shdata;
t_shinput		*g_shinput;
t_current_input	*g_current_in;
t_taskmast		g_taskmast;

int		g_i = 0;

void		*myThreadFun(void *argv)
{
	g_i = 10;
	return NULL;
}

int		main(int argc, const char **argv, const char **envp)
{
	pthread_t tid; 
	printf("Before Thread\n");
	pthread_create(&tid, NULL, &myThreadFun, NULL);
	pthread_join(tid, NULL);
	printf("After Thread %d\n", g_i);
	
	return 0;
	
	init_shell(envp);

	// if (argc <= 1)
	// 	ft_proj_err("A configuartion file must be specified", TRUE);
	
	term_restore_to_old_term_data();
	init_taskmaster("./aux/taskmaster.cngf");
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
