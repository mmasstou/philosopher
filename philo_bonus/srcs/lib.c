#include "../philo_bonus.h"

static int	is_instring(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = -1;
	while (str[++index])
		;
	return (index);
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

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write (fd, s++, 1);
	write (fd, "\n", 1);
}