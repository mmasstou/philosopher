/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:52:26 by mmasstou          #+#    #+#             */
/*   Updated: 2022/06/21 10:08:47 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	pthread_mutex_lock(&(philo->data->wirteing));
	ft_putnbr_fd(get_time() - philo->data->simulation_start, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	ft_putnbr_fd(id, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, string, ft_strlen(string));
	write(STDOUT_FILENO, "\n", 1);
	if (!ft_strstr("died", string))
		pthread_mutex_unlock(&(philo->data->wirteing));
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
