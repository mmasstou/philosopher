/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:52:26 by mmasstou          #+#    #+#             */
/*   Updated: 2022/06/20 19:40:37 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_pthread_mutex_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->right_fork));
	pthread_mutex_unlock(&(philo->left_fork));
	return (NULL);
}

int	eating_count(t_philo *philo)
{
	t_philo	*phi;

	phi = philo;
	while (phi)
	{
		if (phi->nbr_eating < phi->data->args.number_of_times_must_eat)
			return (0);
		phi = phi->next;
	}
	return (1);
}

unsigned long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
