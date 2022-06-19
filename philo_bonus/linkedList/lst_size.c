#include "../philo_bonus.h"

int	ft_lstsize(t_philo *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}