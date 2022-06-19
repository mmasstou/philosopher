#include "../philo_bonus.h"

t_philo	*lstlast(t_philo *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}