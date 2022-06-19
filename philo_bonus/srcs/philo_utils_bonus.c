#include "../philo_bonus.h"

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

// print
static size_t	ft_strlen(const char *s)
{
	size_t	strlen;

	strlen = 0;
	while (s[strlen] != '\0')
		strlen ++;
	return (strlen);
}

static void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		write(fd, "-", 1);
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
	{
		nb += '0';
		write(fd, &nb, 1);
	}
}

static char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j ++;
		}
		i ++;
	}
	return (0);
}

void	print_action(t_philo *philo, int id, char *string)
{
	// printf("\nphilo id :%d\n",id);
	sem_wait(philo->data->wirteing);
	ft_putnbr_fd(get_time() - philo->data->simulation_start, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	ft_putnbr_fd(id, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, string, ft_strlen(string));
	write(STDOUT_FILENO, "\n", 1);
	if (!ft_strstr("died", string))
		sem_post(philo->data->wirteing);
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
