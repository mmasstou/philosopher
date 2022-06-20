/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:52:12 by mmasstou          #+#    #+#             */
/*   Updated: 2022/06/20 19:38:32 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_instring(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

static int	ft_isspace(int s)
{
	char	*space;

	space = "\f\n\r\t\v ";
	while (*space)
		if (s == *space++)
			return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	signe;
	int	result;

	signe = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signe = -signe;
		str++ ;
	}
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + *str - 48;
		str++;
	}
	result *= signe;
	return (result);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	int		index;
	int		jndex;
	int		zndex;

	if (!s1)
		return (NULL);
	jndex = ft_strlen(s1);
	while (s1[--jndex] && is_instring(s1[jndex], set))
		;
	index = -1;
	while (s1[++index] && is_instring(s1[index], set))
		;
	if (jndex == -1)
		jndex = index;
	zndex = jndex - index;
	strtrim = (char *)malloc(zndex + 2);
	if (!strtrim)
		return (NULL);
	zndex = index;
	while (s1[index] && index <= jndex)
		*strtrim++ = s1[index++];
	*strtrim = 0;
	return (strtrim - (index - zndex));
}
