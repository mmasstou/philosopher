/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:49:36 by mmasstou          #+#    #+#             */
/*   Updated: 2022/06/20 18:53:30 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = NULL;
	data->simulation_ended = 0;
	while (++i <= data->args.number_of_philosophers)
		add_back(&philo, lstnew(i, data));
	data->head = philo;
	return (philo);
}

void	ft_destroy_mutexes(t_philo *philo, int i)
{
	while (philo && i != 0)
	{
		pthread_mutex_destroy(&philo->right_fork);
		usleep(50);
		i--;
	}
}

int	init_mutexs(t_philo *philo)
{
	t_philo	*temp;
	int		i;

	i = 0;
	if (pthread_mutex_init(&(philo->data->wirteing), NULL))
		return (false);
	temp = philo;
	while (temp)
	{
		if (pthread_mutex_init(&(temp->right_fork), NULL))
			return (ft_destroy_mutexes(temp, i), free(philo), false);
		i++;
		temp = temp->next;
	}
	return (true);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;
	t_philo	*temp;
	int		i;

	if ((argc < 5 || argc > 6))
		return (ft_putendl_fd("Error", STDERR_FILENO), 1);
	if (ft_parse(argc, argv + 1, &data.args) != 0)
		return (1);
	philo = init_philos(&data);
	if (!philo)
		return (1);
	if (init_mutexs(philo) == false)
		return (1);
	i = _starting(&data, philo);
	ft_destroy_mutexes(philo, data.args.number_of_philosophers);
	while (philo)
	{
		temp = philo->next;
		free(philo);
		philo = temp;
	}
	data.head = NULL;
	philo = NULL;
	return (i);
}
