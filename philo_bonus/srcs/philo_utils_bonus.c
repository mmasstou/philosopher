#include "../philo_bonus.h"

long long	get_time(void)
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

void	print_action(t_philo *philo, int id, char *string)
{
	sem_wait(philo->data->wirteing);
	printf("%lld %d %s\n", get_time() - philo->data->simulation_start, id, string);
	if (!ft_strstr("died", string))
		sem_post(philo->data->wirteing);
}

void	sleep_time(long long time)
{
	long long	i;

	i = get_time();
	while (1)
	{
		if ((get_time() - i) >= time)
			break ;
		usleep(10);
	}
}
