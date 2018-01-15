#include "taskmaster42.h"
#include <wait.h>

t_bool		proc_has_to_be_restarted(
				const t_process *proc,
				int waitpid_status,
				t_bool consider_restart_attempts)
{
	const int	*exit_codes;

	if (g_taskmast.is_exiting)
		return FALSE;
	if (proc->config->restart_mode == e_never)
		return FALSE;
	if (proc->config->restart_mode == e_always)
	{
		if (consider_restart_attempts)
			return proc->status.attempt < proc->config->restart_attempts;
		else
			return TRUE;
	}
	
	exit_codes = proc->config->expected_exit_codes;
	return is_expected_exit_cde(WEXITSTATUS(waitpid_status), exit_codes);
}
