/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:56:13 by mmasstou          #+#    #+#             */
/*   Updated: 2022/06/20 21:26:16 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define PEATING	"is eating"
# define PSLEEOING	"is sleeping"
# define PTEANKING	"is thinking"
# define PDEAD		"died" 
# define PRFORK		"has taken a fork"
# define PLFORK		"has taken a fork"

# define _END  "\x1b[0m"
# define _GREY  "\x1b[30m"
# define _RED  "\x1b[31m"
# define _GREEN  "\x1b[32m"
# define _YELLOW  "\x1b[33m"
# define _BLUE  "\x1b[34m"
# define _PURPLE  "\x1b[35m"
# define _CYAN  "\x1b[36m"
# define _WHITE  "\x1b[37m"

typedef struct args
{
	int				number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_of_times_must_eat;
}	t_args;

typedef struct data
{
	t_args			args;
	struct s_philo	*head;
	pthread_mutex_t	wirteing;
	long			simulation_start;
	int				simulation_ended;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	long			last_time_eat;
	int				nbr_eating;
	t_data			*data;
	struct s_philo	*next;
}	t_philo;
// linked List
t_philo			*lstnew(int id, t_data *data);
void			add_back(t_philo **lst, t_philo *new);
void			add_front(t_philo **lst, t_philo *new);
int				ft_lstsize(t_philo *lst);
t_philo			*lstlast(t_philo *lst);
// philo_ustils
unsigned long	get_time(void);
int				ft_isdigit( int d);
int				str_digit(char	*str);
void			*ft_pthread_mutex_unlock(t_philo *philo);
int				eating_count(t_philo *philo);
int				death_check(t_philo *phi, t_data *data);
// lib
char			*ft_strtrim(char const *s1, char const *set);
int				ft_atoi(const char *str);
void			ft_putendl_fd(char *s, int fd);
size_t			ft_strlen(const char *str);
void			ft_putnbr_fd(int n, int fd);
char			*ft_strstr(const char *haystack, const char *needle);
// ft_parse
int				ft_parse(int argc, char *argv[], t_args *args);
void			print_action(t_philo *philo, int id, char *string);
void			sleep_time(unsigned long time);
int				_starting(t_data *data, t_philo *phi);
int				eating_count(t_philo *philo);
int				cheack_death(t_philo *phi);
#endif
