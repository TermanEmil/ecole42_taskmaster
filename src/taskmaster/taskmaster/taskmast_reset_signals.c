#include "taskmaster42.h"

void	taskmast_reset_signals()
{
	ft_bzero(&g_taskmast.signal_flags, sizeof(g_taskmast.signal_flags));
	g_taskmast.signal_flags.its_safe = TRUE;
}
