#ifndef _TASKMASTER42_H_
# define _TASKMASTER42_H_

# include "libft.h"
# include "hashtablib.h"
# include "listlib.h"
# include "shellvars.h"
# include "process42.h"
# include "shell42.h"
# include "termlib.h"
# include "tskmst_events.h"

#include <signal.h>
#include <pthread.h>

# define TASKMAST_ERROR(EXIT_BOOL, FORMAT, ...)		\
{													\
	taskmast_log(FORMAT, __VA_ARGS__);				\
	if (term_get_data()->is_raw)					\
	{												\
		term_move_cursor_to_left_most();			\
		ft_prerror(EXIT_BOOL, FORMAT, __VA_ARGS__);	\
		term_putnewl();								\
		input_reprint(g_current_in);				\
	}												\
	else											\
		ft_prerror(EXIT_BOOL, FORMAT, __VA_ARGS__);	\
}													\

# define TASKMAST_LOG(FORMAT, ...)					\
{													\
	taskmast_log(FORMAT, __VA_ARGS__);				\
	if (g_taskmast.logger.log_to_term)				\
	{												\
		if (term_get_data()->is_raw)				\
		{											\
			term_move_cursor_to_left_most();		\
			ft_printf(FORMAT, __VA_ARGS__);			\
			term_putnewl();							\
			input_reprint(g_current_in);			\
		}											\
		else										\
			ft_printf(FORMAT, __VA_ARGS__);			\
	}												\
}													\

typedef struct s_taskmast		t_taskmast;
typedef struct s_alrm_schedl	t_alrm_schedl;

typedef t_list					t_lst_schedl;

extern t_taskmast			g_taskmast;

struct				s_alrm_schedl
{
	pid_t			pid;
	int				tm;
	void			(*f)(t_taskmast*, pid_t);
};

typedef struct		s_tskmst_logger
{
	t_str			log_file_path;
	int				log_file_fd;
	t_bool			log_is_on;
	t_bool			log_to_term;
}					t_tskmst_logger;

typedef struct		s_tskmst_sgnls
{
	t_bool			signals[NSIG];
	t_bool			its_safe;
}					t_tskmst_sgnls;

struct				s_taskmast
{
	t_tskmst_logger	logger;
	t_lst_proccfg	*proc_cfgs;
	t_lst_proc		*procs;
	t_bool			is_exiting;
	t_process		*next_alarm;
	t_lst_schedl	*schedules;
	t_alrm_schedl	*next_schedl;
	t_rostr			cfg_path;
	t_tskmst_sgnls	signal_flags;
	t_event_ctrl	event_ctrl;
	pthread_t		waiter_thread;
};

void		taskmast_log(const char *format, ...);

/*
** Cmds
*/

int			execute_tskmast_cmd_status(t_cmd_env *cmd_env);
int			execute_tskmast_cmd_start(t_cmd_env *cmd_env);
int			execute_tskmast_cmd_stop(t_cmd_env *cmd_env);
int			execute_tskmast_cmd_restart(t_cmd_env *cmd_env);

/*
** Cmds helpers
*/

void		print_general_status(const t_lst_proc *procs);

/*
** Constr & Destrs
*/

void			init_taskmaster(t_rostr config_file);
void			del_taskmast(t_taskmast *taskmast);
t_alrm_schedl	new_alarm_schedule(pid_t pid, int schedule_time,
					void (*f)(t_taskmast*, pid_t));

int				taskmast_load_all_config(const t_shvars *shvars,
					t_taskmast *taskmast, t_rostr file_path);
int				load_taskmaster_config(t_taskmast *taskmast,
					t_lst_str *lines);

/*
** Taskmaster in general
*/

void		taskmast_start(t_taskmast *taskmast);
void		setup_alarm(t_taskmast *taskmast, t_alrm_schedl schedl);
void		update_alarm();
void		destroy_proc_intance(t_taskmast *taskmast, t_process *proc);

/*
** Signals
*/

void		taskmast_reset_signals();
void		taskmast_parse_signals();

/*
** Reloading.
*/

void		reload_taskmast_config(t_taskmast *taskmast,
				const t_shvars *shvars, t_rostr file_path);
void		reload_procs_config(t_taskmast *taskmast, t_lst_proccfg *new_cfgs);
void		grace_stp_procs_with_config(t_taskmast *taskmast,
				const t_proc_config *cfg);

/*
** Utils
*/

void		taskmast_setup_logger(t_taskmast *taskmast);
void		execute_function_from_strcmd(t_rostr cmd, t_lst_proc *procs,
				t_rostr err_msg, void (*f)(t_process*));
void		create_processes(t_taskmast *taskmast, t_lst_proccfg *proc_cfgs);
void		remove_schedule(t_alrm_schedl *schedule);
void		sigkill_pid(t_taskmast *taskmaster, pid_t pid);
t_alrm_schedl	*get_min_time_schedule(const t_lst_schedl *schedules);

#endif