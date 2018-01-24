#include "shinput.h"
#include "shlogic.h"
#include "shell42.h"
#include "regex_tools.h"
#include "shell_redirs_.h"
#include "taskmaster42.h"

t_bool			argv_represents_a_subshell_(const t_str *argv)
{
	return argv[0] != NULL && argv[1] == NULL &&
		regex_mini_match("^\\(.*\\)", argv[0]);
}

static pid_t	try_execute_from_path_(
					const t_pipe_env *pipe_env,
					t_cmd_env *cmd_env)
{
	t_str	cmd_path;
	pid_t	pid;

	cmd_path = find_cmd_in_env_path(cmd_env->argv[0], pipe_env->shvars, FALSE);
	if (cmd_path)
	{
		pid = execute_cmd(cmd_env, cmd_path);
		free(cmd_path);
		return pid;
	}
	return 0;
}

static pid_t	try_to_execute_argv_(
					const t_pipe_env *pipe_env,
					t_cmd_env *cmd_env)
{
	t_exec_cmd_f	*exec_cmd_f;
	pid_t			pid;

	if (argv_represents_a_subshell_(cmd_env->argv))
		return parse_subshell(cmd_env);
	else if (cmd_env->argv[0] != NULL && cmd_is_set_var(cmd_env->argv[0]))
	{
		execute_cmd_set_local_var(cmd_env);
		return 0;
	}
	else if ((exec_cmd_f = get_sh_builtin_f(cmd_env->argv[0], pipe_env->built_in_cmds)))
	{
		execute_built_in(cmd_env, exec_cmd_f);
		return 0;
	}
	else if (cmd_is_specific_program(cmd_env->argv[0]))
		return execute_cmd(cmd_env, cmd_env->argv[0]);
	else if ((pid = try_execute_from_path_(pipe_env, cmd_env)) != 0)
		return pid;
	return -42;
}

pid_t			process_argv(t_pipe_env *pipe_env, t_cmd_env *cmd_env)
{
	pid_t			ret;

	if (cmd_env->argv[0] == NULL)
		return 0;

	g_shdata.running_a_process = TRUE;
	ret = try_to_execute_argv_(pipe_env, cmd_env);
	g_shdata.running_a_process = FALSE;

	if (ret != -42)
		return ret;

	ft_error(FALSE, "%s: command not found\n", cmd_env->argv[0]);
	return -1;
}
