#include "../philo_bonus.h"

t_philo	*lstnew(int id, t_data *data)
{
	t_philo	*new_node;

	new_node = malloc(sizeof(t_philo));
	if (!new_node)
		return (0);
	new_node->data = data;
    new_node->id = id;
	new_node->nbr_eating = 0;
	new_node->eated = 0;
	new_node->next = 0;
	return (new_node);
}