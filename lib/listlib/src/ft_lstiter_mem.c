#include "listlib.h"

void			ft_lstiter_mem(t_list *lst, void (*f)(void *content))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
