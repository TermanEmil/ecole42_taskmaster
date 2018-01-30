#ifndef _TASKMAST_LOGGING_H_
# define _TASKMAST_LOGGING_H_

# define TASKMAST_PRINT(PRINT_STATEMENT)									\
{																			\
	if (term_get_data()->is_raw)											\
	{																		\
		term_move_cursor_to_left_most();									\
		PRINT_STATEMENT;													\
		term_move_cursor_to_left_most();									\
	}																		\
	else																	\
		PRINT_STATEMENT;													\
}																			\

# define TASKMAST_ERROR(EXIT_BOOL, FORMAT, ...)								\
{																			\
	taskmast_log(FORMAT, __VA_ARGS__);										\
	TASKMAST_PRINT(															\
		sync_printf(&g_printf_mutex, STDERR_FILENO, FORMAT, __VA_ARGS__));	\
	if (EXIT_BOOL)															\
		event_exit(0);														\
}																			\

# define TASKMAST_LOG(FORMAT, ...)											\
{																			\
	taskmast_log(FORMAT, __VA_ARGS__);										\
	if (g_taskmast.logger.log_to_term)										\
	{																		\
		TASKMAST_PRINT(														\
			sync_printf(&g_printf_mutex,									\
				STDERR_FILENO, FORMAT, __VA_ARGS__));						\
	}																		\
}																			\


#endif