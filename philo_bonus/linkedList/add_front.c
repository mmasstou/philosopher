#include "../philo_bonus.h"

void	add_front(t_philo **lst, t_philo *new)
{
	new->next = *lst;
	*lst = new;
}