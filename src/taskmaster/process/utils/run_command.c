#include "shlogic.h"
#include "taskmaster42.h"

int		run_command(t_rostr cmd, const t_str *env)
{
	t_lst_inkey	*cmd_keys;
	t_lst_words	*words;
	t_str		*argv;
	int			ret;

	cmd_keys = get_sh_inkeys_from_str(cmd);
	if ((ret = assign_what_are_insideof(cmd_keys)) != 0)
	{
		if (ret == -1)
		{
			TASKMAST_ERROR(FALSE, "%s: cmd isn't complete: an unexpected"
				" delim has been detected\n", cmd);
		}
		else
			TASKMAST_ERROR(FALSE, "%s: cmd isn't complete (%c)\n", cmd, ret);
		return -1;
	}
	words = extract_words_from_keys(cmd_keys);
	argv = words_to_argv(words);
	execve(argv[0], argv, env);
	TASKMAST_ERROR(FALSE, "%s: %s\n", argv[0], strerror(errno));
	return -1;
}
