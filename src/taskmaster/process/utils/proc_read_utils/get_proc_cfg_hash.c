#include "config_reader_.h"

size_t		get_proc_cfg_hash(t_lst_str *lines, int lines_count)
{
	size_t	hash;

	hash = 0;
	for (; lines && lines_count >= -1; LTOPREV(lines), lines_count--)
	{
		if (ft_strequ(LSTR(lines), ""))
			continue;
		hash ^= ft_hash(lines->content, lines->content_size);
	}
	return hash;
}
