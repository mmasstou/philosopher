/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:05:24 by mmasstou          #+#    #+#             */
/*   Updated: 2022/06/21 09:58:08 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	philo_error(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
	exit(1);
}
