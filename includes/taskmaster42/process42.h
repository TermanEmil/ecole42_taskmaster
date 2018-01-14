#ifndef _PROCESS_42_H_
# define _PROCESS_42_H_

# include "libft.h"
# include "hashtablib.h"
# include "listlib.h"
# include "shellvars.h"
# include "ft_colors.h"

# define STATE_NOT_STARTED	C_GRAY		"not started"	C_EOC
# define STATE_RUNNING		C_GREEN		"running"		C_EOC
# define STATE_STOPPED		C_YELLOW	"stopped"		C_EOC
# define STATE_COMPLETED	C_CYAN		"completed"		C_EOC
# define STATE_CRITIC		C_RED		"critic"		C_EOC

typedef t_list	t_lst_proc;
typedef t_list	t_lst_proccfg;

typedef enum		e_restart_mode
{
	e_always,
	e_never,
	e_unexpected_exit
}					t_restart_mode;


typedef struct		s_proc_config
{
	t_str			prog_name;
	t_str			launch_cmd;
	int				nb_of_procs;
	t_bool			autostart;
	t_restart_mode	restart_mode;
	int				*expected_exit_codes;
	int				success_time;
	int				restart_attempts;
	int				sig_stop;
	int				time_before_kill;
	t_str			stdout;
	t_str			stderr;
	t_str			*environment;
	t_str			dir;
	mode_t			umask;
}					t_proc_config;

typedef struct		s_proc_status
{
	t_bool			started;
	t_bool			completed;
	t_bool			stopped;
	int				status;
	int				attempt;
}					t_proc_status;

typedef struct		s_proc_time
{
	int				running_time;
	int				start_time;
}					t_proc_time;

typedef struct		s_process
{
	t_proc_config	*config;
	t_str			name;
	int				name_id;
	pid_t			pid;
	t_proc_status	status;
	int				stdin_fd[2];
	int				stdout_fd[2];
	int				stderr_fd[2];
	t_proc_time		proc_time;
}					t_process;

int			process_start(t_process *process);

/*
** Constr & destr
*/

t_process	new_process(t_proc_config *config, const t_lst_proc *processes);
void		del_proc_config(t_proc_config *proc_config);
void		del_proc(t_process *proc);

/*
** Utils
*/

void		run_command(t_rostr cmd, const t_str *env);
int			get_process_name_id(const t_process *proc,
				const t_lst_proc *proccesses);
t_str		new_process_name(const t_process *proc);
void		close_process_open_fds(t_process *process);
int			process_std_redir_to_file(t_rostr std_fd_val, int default_fd);
t_rostr		get_proc_state_str(const t_process *proc);

/*
** Time
*/

int			proc_uptime(const t_process *proc);
t_rostr		proc_struptime(const t_process *proc);

#endif