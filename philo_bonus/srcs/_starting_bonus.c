#include "../philo_bonus.h"

void	philo_eating(t_philo *philo)
{
	sem_wait(philo->data->fork);
	print_action(philo, philo->id, PRFORK);
	sem_wait(philo->data->fork);
	print_action(philo, philo->id, PLFORK);
	// sem_wait(philo->data->eating);
	print_action(philo, philo->id, PEATING);
	philo->last_time_eat = get_time();
	// sem_post(philo->data->eating);
	sleep_time(philo->data->args.time_to_eat);
	philo->nbr_eating++;
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
}

void	*checking_philosopher(void	*philo)
{
	t_philo	*temp;

	temp = (t_philo *)philo;
	 while(1)
	{
		// printf("\nID-%d--(%lu--%ld) = %lu -- %lu\n", temp->id, get_time(), temp->last_time_eat, get_time() - temp->last_time_eat, temp->data->args.time_to_die);
		if (temp->nbr_eating && temp->data->args.number_of_times_must_eat && eating_count(temp))
		{
			temp->data->simulation_ended = 1;
			exit(EXIT_SUCCESS);
		}
		if (get_time() - temp->last_time_eat >= temp->data->args.time_to_die)
		{
			temp->data->simulation_ended = 1;
			print_action(temp, temp->id, PDEAD);
			exit (EXIT_FAILURE);
		}
		usleep(50);
	}
	return (NULL);
}

void	*philo_rotine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (pthread_create(&philo->thread, NULL, &checking_philosopher, (void *)philo))
		philo_error("Error -> thread not created sccusfully", 1);
	if ((philo->id % 2))
		usleep(1500);
	while (philo->data->simulation_ended != 1)
	{
		philo_eating(philo);
		print_action(philo, philo->id, PSLEEOING);
		sleep_time(philo->data->args.time_to_sleep);
		print_action(philo, philo->id, PTEANKING);
	}
	return (NULL);
}

void	ft_waitpid(t_philo **phi)
{
	int		status;
	t_philo	*tmp;

	tmp = *phi;
	while (tmp)
	{
		waitpid(-1, &status, 0);
		if (status == 0)
			tmp = tmp->next;
		else if (status != 0)
		{
			while (tmp)
			{
				kill(tmp->data->pid, SIGKILL);
				tmp = tmp->next;
			}
			exit(1);
		}
	}
}

int _starting_bonus(t_philo *phi)
{
	while (phi)
	{
		phi->data->pid = fork();
		if (phi->data->pid == -1)
			philo_error("Error -> fork", 1);
		else if (phi->data->pid == 0)
		{
			phi->last_time_eat = get_time();
			philo_rotine(phi);
		}
		else
			phi = phi->next;
	}
	ft_waitpid(&phi);
	return(EXIT_SUCCESS);
}