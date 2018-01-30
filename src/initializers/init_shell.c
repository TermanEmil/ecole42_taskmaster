#include "shell42.h"
#include "shlogic.h"

static inline void	init_global_links(void)
{
	ft_err_init_proj_name("taskmaster");

	g_current_in = &g_shdata.input.current;
	g_shinput = &g_shdata.input;
}

void	init_shell(const char **envp)
{
	g_shdata = shdata_construct();

	g_shdata.is_term = isatty(STDOUT_FILENO);
	errno = 0;

	init_global_links();

	if (g_shdata.is_term)
	{
		term_setup(getenv("TERM"), term_get_data());	
		term_make_termcap_keys_work();
		g_shdata.input.term_tty = term_get_current_tty();
	}
	
	g_shdata.shvars = shvars_construct(envp);
	g_shdata.built_in_cmds = init_built_in_cmds_htab();
	shell_init_key_cmds_htab();

	init_sh_events();
	ft_strcpy(g_shdata.prompt, DEFAULT_PROMPT);
}
