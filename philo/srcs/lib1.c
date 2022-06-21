/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:52:12 by mmasstou          #+#    #+#             */
/*   Updated: 2022/06/21 10:15:13 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit( int d)
{
	return (d >= '0' && d <= '9');
}

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = -1;
	while (str[++index])
		;
	return (index);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write (fd, s++, 1);
	write (fd, "\n", 1);
}
