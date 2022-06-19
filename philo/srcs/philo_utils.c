#include "../philo.h"

unsigned long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_isdigit( int d)
{
	return (d >= '0' && d <= '9');
}

int	str_digit(char	*str)
{
	int		i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i + 1] == '\0')
			return (1);
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	cheack_death(t_philo *phi)
{
	t_philo	*tmp;

	tmp = phi;
	while (tmp)
	{
		if (tmp->data->simulation_ended == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	print_action(t_philo *philo, int id, char *string)
{
	if (philo->data->simulation_ended != 1)
	{
		pthread_mutex_lock(&(philo->data->wirteing));
		printf("%lu %i %s\n",get_time() - philo->data->simulation_start, id, string);
		pthread_mutex_unlock(&(philo->data->wirteing));
	}
	else if (philo->data->simulation_ended == 1)
	{
		usleep(100);
		pthread_mutex_lock(&(philo->data->wirteing));
		printf("%lu %i %s\n",get_time() - philo->data->simulation_start, id, string);
	}
}

void	sleep_time(unsigned long time)
{
	unsigned long	i;

	i = get_time();
	while (1)
	{
		if ((get_time() - i) >= time)
			break ;
		usleep(100);
	}
}