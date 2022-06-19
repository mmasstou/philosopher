#include "../philo_bonus.h"

void	philo_eating(t_philo *philo)
{
	sem_wait(philo->data->fork);
	print_action(philo, philo->id, PRFORK);
	sem_wait(philo->data->fork);
	print_action(philo, philo->id, PLFORK);
	sem_wait(philo->data->eating);
	philo->last_time_eat = get_time();
	print_action(philo, philo->id, PEATING);
	philo->nbr_eating++;
	sem_post(philo->data->eating);
	sleep_time(philo->data->args.time_to_eat);
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
}

void	*checking_philosopher(void	*philo)
{
	t_philo	*temp;

	temp = (t_philo *)philo;
	 while(temp)
	{
		usleep(150);
		if (temp->nbr_eating && temp->data->args.number_of_times_must_eat && eating_count(temp))
		{
			temp->data->simulation_ended = 1;
			exit(EXIT_SUCCESS);
		}
		if (get_time() - temp->last_time_eat >= temp->data->args.time_to_die)
		{
			printf("ID-%d--(%lu--%ld) = %lu -- %lu", temp->id, get_time(), temp->last_time_eat, get_time() - temp->last_time_eat, temp->data->args.time_to_die);
			temp->data->simulation_ended = 1;
			print_action(temp, temp->id, PDEAD);
			exit (EXIT_FAILURE);
		}
		if (temp->next == NULL)
			temp = temp->data->head;
		else
			temp = temp->next;
	}
	return (NULL);
}

void	*philo_rotine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	printf("\n**id %d***%lu\n",philo->id,philo->last_time_eat);
	if (!(philo->id % 2))
		usleep(1500);
	if (pthread_create(&philo->thread, NULL, &checking_philosopher, (void *)philo))
		philo_error("Error -> thread not created sccusfully", 1);
	
	while (philo->data->simulation_ended != 1)
	{
		philo_eating(philo);
		print_action(philo, philo->id, PSLEEOING);
		sleep_time(philo->data->args.time_to_sleep);
		print_action(philo, philo->id, PTEANKING);
	}
	return (NULL);
}

void	ft_kill(t_data *da)
{
	int		index;

	index = 0;
	while (index < da->args.number_of_philosophers)
	{
		kill(da->pid[index], SIGKILL);
		index++;
	}
	exit(1);
}
int _starting_bonus(t_data *data, t_philo *phi)
{
	t_philo	*tmp;
	int		index;
	int		status;

	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->args.number_of_philosophers);
	if (!data->pid)
		philo_error("Error -> malloc", 1);
	tmp = phi;
	index = 0;
	while (tmp)
	{
		phi->id = index + 1;
		data->pid[index] = fork();
		if (data->pid[index] == -1)
			philo_error("Error -> fork", 1);
		if (data->pid[index] == 0)
		{
			phi->last_time_eat = get_time();
			phi->last_time_eat = get_time();
			philo_rotine(phi);
		}
		index++;
		tmp = tmp->next;
	}
	waitpid(-1, NULL, 0);
	while (tmp)
	{
		waitpid(-1, &status, 0);
		if (status == 0)
			tmp = tmp->next;
		else if (status != 0)
			ft_kill(data);
	}

	return(EXIT_SUCCESS);
}