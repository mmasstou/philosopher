/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _starting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:51:37 by mmasstou          #+#    #+#             */
/*   Updated: 2022/06/20 19:08:24 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_eating(t_philo *philo)
{
	t_philo	*next;

	if (philo->next == NULL)
		next = philo->data->head;
	else
		next = philo->next;
	if (philo->data->simulation_ended != 1)
	{
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
	else if (philo->data->simulation_ended != 0)
		return (ft_pthread_mutex_unlock(philo));
	return (NULL);
}

void	*philo_rotine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (!(philo->id % 2))
		usleep(1000);
	while (philo->data->simulation_ended == 0)
	{
		if (philo_eating(philo) == NULL && philo->data->simulation_ended == 1)
			return (NULL);
		print_action(philo, philo->id, PSLEEOING);
		sleep_time(philo->data->args.time_to_sleep);
		print_action(philo, philo->id, PTEANKING);
	}
	return (NULL);
}

int	death_check(t_philo *phi, t_data *data)
{
	t_philo	*temp;

	temp = phi;
	while (temp)
	{
		if (temp->nbr_eating && data->args.number_of_times_must_eat && \
			eating_count(temp))
			return (data->simulation_ended = 1, EXIT_SUCCESS);
		if (get_time() - temp->last_time_eat >= temp->data->args.time_to_die)
		{
			data->simulation_ended = 1;
			usleep(50);
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

int	_starting(t_data *data, t_philo *phi)
{
	t_philo	*temp;
	int		index;

	temp = phi;
	data->simulation_start = get_time();
	while (temp)
	{
		if (pthread_create(&temp->thread, NULL, philo_rotine, temp))
			return (EXIT_FAILURE);
		temp->last_time_eat = get_time();
		temp = temp->next;
	}
	index = death_check(phi, data);
	return (index);
}
