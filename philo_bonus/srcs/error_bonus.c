/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:05:24 by mmasstou          #+#    #+#             */
/*   Updated: 2022/06/21 00:05:56 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	philo_error(char *error_msg, int type)
{
	(void)type;
	ft_putendl_fd(error_msg, STDERR_FILENO);
	system("leaks philo");
	exit(1);
}
