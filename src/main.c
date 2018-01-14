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

void		process_normal_exit(t_process *proc, int status)
{
	TASKMAST_LOG("Process %s, pid: %d exited with the code %d\n",
		proc->name, proc->pid, WEXITSTATUS(status));
}

void		process_signal_exit(t_process *proc, int status)
{
	TASKMAST_LOG("Process %s, pid: %d signal exited with the signal %d\n",
		proc->name, proc->pid, WTERMSIG(status));
}

void		process_stopped(t_process *proc, int status)
{
	TASKMAST_LOG("Process %s, pid: %d stopped with the signal %d\n",
		proc->name, proc->pid, WSTOPSIG(status));
}

void		process_continue(t_process *proc, int status)
{
	TASKMAST_LOG("Process %s, pid: %d continued\n", proc->name, proc->pid);
}

void		wait_nohang_process(t_process *process)
{
	pid_t	pid;
	int		status; 
	pid_t	ret;

	ret = TMP_FAIL_RETRY(waitpid(process->pid, &status, WNOHANG));
	errno = 0;
	if (ret == -1)
	{
		if (errno != ECHILD && errno != 0)
		{
			TASKMAST_ERROR(TRUE, "Failed to waitpid(): %s %d\n",
				strerror(errno));
		}
		errno = 0;
	}
	else if (ret != 0)
	{
		if (WIFEXITED(status))
			process_normal_exit(process, status);
		else if (WIFSIGNALED(status))
			process_signal_exit(process, status);
		else if (WIFSTOPPED(status))
			process_stopped(process, status);
		else if (WIFCONTINUED(status))
			process_continue(process, status);
		else
			TASKMAST_ERROR(FALSE, "Invalid waitpid() status: %d\n", status);
	}
}

void		*continous_update_processes_stats()
{
	pid_t	pid;
	int		status;

	while (!g_taskmast.thread_should_die)
	{
		ft_lstiter_mem(g_taskmast.procs, (void (*)(void*))&wait_nohang_process);
		usleep(150);
	} 
	return NULL;
}

int		main(int argc, const char **argv, const char **envp)
{	
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
