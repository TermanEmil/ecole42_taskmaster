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
# define STATE_GRACE_STOP	C_LCYAN		"grace stop"	C_EOC

# define PROC_SCHEDL_USR_RESTART (1 << 0)

#define ISSTATE(PROC, STATE) ((PROC)->status.state == STATE)

typedef t_list	t_lst_proc;
typedef t_list	t_lst_proccfg;

typedef enum		e_restart_mode
{
	e_always,
	e_never,
	e_unexpected_exit
}					t_restart_mode;

enum				e_proc_state
{
	e_not_started = 1,
	e_running,
	e_stopped,
	e_completed,
	e_critic,
	e_grace_stopping
};

/*
** nprocs
** autostart
** restart_mode
** success_time
** restart_attempts
** sig_stop
** time_before_kill
** umask
** expected_exit_codes
** environment
** dir
*/

typedef struct		s_proc_config
{
	t_str			prog_name;
	t_str			launch_cmd;
	int				nb_of_procs;
	t_bool			autostart;
	t_restart_mode	restart_mode;
	int				*expected_exit_statuss;
	int				success_time;
	int				restart_attempts;
	int				sig_graceful_stop;
	int				time_before_forced_kill;
	t_str			stdout;
	t_str			stderr;
	t_str			*environment;
	t_str			dir;
	mode_t			umask;
	size_t			hash;
}					t_proc_config;

typedef struct			s_proc_status
{
	enum e_proc_state	state;
	int					waitpid_status;
	int					attempt;
	int					sig_on_kill;
}						t_proc_status;

typedef struct		s_proc_time
{
	int				running_time;
	int				start_time;
	int				finish_time;
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
	int				schedule_actions;
}					t_process;

/*
** Core
*/

int			process_start(t_process *process);
void		child_process_start(t_process *proc);
void		father_process_start(t_process *proc);

int			stop_process(t_process *proc);
int			restart_process(t_process *proc);
int			continue_process(t_process *proc);
void		proc_graceful_stop(t_process *proc);

/*
** Waitpid parsers
*/

void		parse_process_waitpid(pid_t waited_pid, int wait_status);
void		process_normal_exit(t_process *proc, int status);
void		process_signal_exit(t_process *proc, int status);
void		process_stopped(t_process *proc, int status);
void		process_continue(t_process *proc, int status);

void		update_proc_state(t_process *proc);
int			raw_proc_kill(int signum, pid_t pid, t_rostr proc_name,
				t_rostr struptime);
int			kill_proc(int signum, t_process *proc);
void		kill_processes(int signum, const t_lst_proc *procs);
t_rostr		get_proc_description(const t_process *proc);

/*
** Constr & destr
*/

t_process	new_process(const t_proc_config *config, int name_id);
void		del_proc_config(t_proc_config *proc_config);
void		del_proc(t_process *proc);

/*
** Utils
*/

int			get_process_name_id(t_rostr proc_prog_name,
				const t_lst_proc *proccesses);
int			new_unique_name_id(t_rostr default_name,
				const t_lst_proc *procs);
t_str		new_process_name(t_rostr default_name, int name_id);
void		close_process_open_fds(t_process *process);
int			process_std_redir_to_file(t_rostr std_fd_val, int default_fd);
t_rostr		get_proc_state_str(const t_process *proc);
t_bool		is_expected_exit_status(int code, const int *expected_exit_codes);
t_bool		proc_has_to_be_restarted(const t_process *proc, int waitpid_status,
				t_bool consider_restart_attempts);
void		discard_proc_redirs(t_process *proc);
int			pipe_process(t_process *proc);
int			proc_mv_to_dir(t_rostr dir);

/*
** Proc config utils.
*/

t_proc_config	*proc_config_dup(const t_proc_config *cfg);

/*
** List utils
*/

t_bool		proc_cfg_hash_equ(const size_t *hash, const t_proc_config *config);
t_bool		proc_ref_equ(const t_process *proc1, const t_process *proc2);
t_bool		proc_is_state(enum e_proc_state *state, const t_process *proc);

/*
** Getters
*/

t_process	*lst_process_pidof(const t_lst_proc *procs, pid_t pid);
t_process	*lst_proc_pidof_grac_stop(const t_lst_proc *procs, pid_t pid);
t_process	*lst_proc_pidof_no_grac_stop(const t_lst_proc *procs, pid_t pid);
t_process	*lst_get_proc_with_name(const t_lst_proc* procs, t_rostr name);
t_lst_proc	*lst_get_procs_matching_name(const t_lst_proc* procs, t_rostr name);
t_process	*lst_get_proc_with_pidname(const t_lst_proc* prcs, t_rostr pidname);
t_lst_proc	*get_processes_from_strcmd(const t_lst_proc *procs, t_rostr cmd);
enum e_proc_state	get_state_from_str(t_rostr str);

/*
** Time
*/

int			proc_uptime(const t_process *proc);
t_rostr		proc_struptime(const t_process *proc);

#endif