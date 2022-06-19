#include "../philo.h"

void	add_back(t_philo **lst, t_philo *new)
{
	t_philo	*last_node;

	if (!*lst)
	{
		add_front(lst, new);
		return ;
	}
	last_node = lstlast(*lst);
	last_node->next = new;
}