/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:06:37 by mmasstou          #+#    #+#             */
/*   Updated: 2022/06/21 09:56:15 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static int	cheak_max_int(long *nbr, char str, int *i)
{	
	if (ft_isdigit(str) != true)
		philo_error("Error");
	*nbr = (*nbr) * 10 + str - 48;
	if (*nbr < INT_MIN || *nbr > INT_MAX)
		philo_error("Error");
	(*i)++;
	return (true);
}

int	arg_isdigit(char *str)
{
	int		i;
	int		signe;
	long	result;

	i = 0;
	signe = 1;
	result = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			philo_error("Error signe");
		if (str[i + 1] == '\0')
			philo_error("Error");
		i++;
	}
	result *= signe;
	while (str[i])
		if (!cheak_max_int(&result, str[i], &i))
			return (false);
	return (result);
}

int	min_args(t_args *args)
{
	if (args->number_of_philosophers < 1 \
		|| args->time_to_die < 1 \
		|| args->time_to_eat < 1 \
		|| args->time_to_sleep < 1)
		philo_error("min value !");
	return (true);
}

int	ft_parse_bonus(int argc, char *argv[], t_args *args)
{
	int	index;
	int	jndex;

	index = -1;
	while (argv[++index])
	{
		jndex = -1;
		while (argv[index][++jndex] == ' ')
			;
		if (argv[index][jndex] == '\0' || !arg_isdigit(&argv[index][jndex]))
			philo_error("Error !");
	}
	args->number_of_philosophers = arg_isdigit(argv[0]);
	args->time_to_die = arg_isdigit(argv[1]);
	args->time_to_eat = arg_isdigit(argv[2]);
	args->time_to_sleep = arg_isdigit(argv[3]);
	if (argc > 5)
		args->number_of_times_must_eat = arg_isdigit(argv[4]);
	else
		args->number_of_times_must_eat = -1;
	min_args(args);
	return (0);
}
