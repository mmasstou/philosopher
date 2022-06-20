/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:10:59 by mmasstou          #+#    #+#             */
/*   Updated: 2022/06/21 00:11:06 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	print_action(t_philo *philo, int id, char *string)
{
	sem_wait(philo->data->wirteing);
	printf("%lld %d %s\n", get_time() - \
	philo->data->simulation_start, id, string);
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
