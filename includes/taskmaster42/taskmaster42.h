#ifndef _TASKMASTER42_H_
# define _TASKMASTER42_H_

# include "libft.h"
# include "hashtablib.h"
# include "listlib.h"
# include "shellvars.h"
# include "process42.h"
# include "shell42.h"
# include "termlib.h"

#include <pthread.h>

# define TASKMAST_ERROR(EXIT_BOOL, FORMAT, ...)					\
			{													\
				ft_prerror(EXIT_BOOL, FORMAT, __VA_ARGS__);		\
				taskmast_log(FORMAT, __VA_ARGS__);				\
			}													\

# define TASKMAST_LOG(FORMAT, ...)								\
			taskmast_log(FORMAT, __VA_ARGS__);					\


typedef struct s_taskmast	t_taskmast;

extern t_taskmast			g_taskmast;

typedef struct		s_tskmst_logger
{
	t_str			log_file_path;
	int				log_file_fd;
	t_bool			log_is_on;
	t_bool			log_to_term;

}					t_tskmst_logger;

struct				s_taskmast
{
	t_tskmst_logger	logger;
	t_lst_proccfg	*proc_cfgs;
	t_lst_proc		*procs;
	t_bool			is_exiting;
	t_process		*next_alarm;
};

void		taskmast_log(const char *format, ...);

/*
** Cmds
*/

int			execute_tskmast_cmd_status();
int			execute_tskmast_cmd_start(t_cmd_env *cmd_env);

/*
** Constr & Destrs
*/

void		init_taskmaster(t_rostr config_file);
void		del_taskmast(t_taskmast *taskmast);

int			taskmast_load_all_config(const t_shvars *shvars,
				t_taskmast *taskmast, t_rostr file_path);

/*
** Taskmaster in general
*/

void		taskmast_start(t_taskmast *taskmast);
void		update_alarm();

#endif