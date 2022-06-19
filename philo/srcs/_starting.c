#include "../philo.h"

void	philo_eating(t_philo *philo)
{
	t_philo	*next;

	if (philo->next == NULL)
		next = philo->data->head;
	else
		next = philo->next;
	pthread_mutex_lock(&(philo->right_fork));
	print_action(philo, philo->id, PRFORK);
	pthread_mutex_lock(&(next->right_fork));
	print_action(philo, philo->id, PLFORK);
	print_action(philo, philo->id, PEATING);
	philo->last_time_eat = get_time();
	philo->nbr_eating++;
	sleep_time(philo->data->args.time_to_eat);
	pthread_mutex_unlock(&(philo->right_fork));
	pthread_mutex_unlock(&(next->right_fork));
}

void	*philo_rotine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (!(philo->id % 2))
		usleep(500);
	// philo->last_time_eat = get_time();
	while (philo->data->simulation_ended != 1)
	{
		philo_eating(philo);
		// if (philo->nbr_eating && philo->data->args.number_of_times_must_eat && eating_count(philo))
		// 	return (philo->data->simulation_ended = 1, NULL);
		print_action(philo, philo->id, PSLEEOING);
		sleep_time(philo->data->args.time_to_sleep);
		print_action(philo, philo->id, PTEANKING);
	}
	return (NULL);
}

int	eating_count(t_philo *philo)
{
	t_philo *phi;

	phi = philo;
	while(phi)
	{
		if (phi->nbr_eating < phi->data->args.number_of_times_must_eat)
			return (0);
		phi = phi->next;
	}
	return (1);
}
// temp->last_time_eat + data->args.time_to_die <= get_time() - data->simulation_start
void	simulation_started(t_philo **phi, unsigned long i)
{
	t_philo	*p;

	p = *phi;
	while (p)
	{
		p->data->simulation_start = i;
		p->data->simulation_ended = 0;
		p = p->next;
	}
}
int _starting(t_data *data, t_philo *phi)
{
	t_philo	*temp;

	temp = phi;
	data->simulation_start = get_time();

    // simulation_started(&phi, get_time());
    while (temp)
    {
        if (pthread_create(&temp->thread, NULL,  philo_rotine, temp))
            return (EXIT_FAILURE);
		temp->last_time_eat = get_time();
		temp = temp->next;
    }
	temp = phi;
    while(temp)
	{
		// usleep(50);
		if (temp->nbr_eating && data->args.number_of_times_must_eat && eating_count(temp))
			return (data->simulation_ended = 1, EXIT_SUCCESS);
		if (get_time() - temp->last_time_eat >= temp->data->args.time_to_die)
		{
			data->simulation_ended = 1;
			print_action(temp, temp->id, PDEAD);
			return (EXIT_SUCCESS);
		}
		if (temp->next == NULL)
			temp = data->head;
		else
			temp = temp->next;
	}
	return (EXIT_SUCCESS);
}