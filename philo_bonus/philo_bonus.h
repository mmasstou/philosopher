/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:00:01 by mmasstou          #+#    #+#             */
/*   Updated: 2022/06/21 09:55:37 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <limits.h>

# define PEATING	"is eating"
# define PSLEEOING	"is sleeping"
# define PTEANKING	"is thinking"
# define PDEAD		"died" 
# define PRFORK		"has taken a fork"
# define PLFORK		"has taken a fork"
# define SEM_FORK "fork"
# define SEM_WIRTE "wirte"

typedef struct args
{
	int		number_of_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		number_of_times_must_eat;
}	t_args;
typedef struct data
{
	t_args			args;
	struct s_philo	*head;
	sem_t			*fork;
	sem_t			*wirteing;
	sem_t			*eating;
	long			simulation_start;
	int				simulation_ended;
}	t_data;
typedef struct s_philo
{
	int				id;
	pid_t			pid;
	pthread_t		thread;
	long			last_time_eat;
	int				nbr_eating;
	int				eated;
	t_data			*data;
	struct s_philo	*next;
}	t_philo;

// linked List
t_philo		*lstnew(int id, t_data *data);
void		add_back(t_philo **lst, t_philo *new);
void		add_front(t_philo **lst, t_philo *new);
int			ft_lstsize(t_philo *lst);
t_philo		*lstlast(t_philo *lst);
// philo_ustils
long long	get_time(void);
int			ft_isdigit( int d);
// lib
void		ft_putendl_fd(char *s, int fd);
char		*ft_strstr(const char *haystack, const char *needle);
// ft_parse
int			ft_parse_bonus(int argc, char *argv[], t_args *args);
void		print_action(t_philo *philo, int id, char *string);
void		sleep_time(long long time);
int			_starting_bonus(t_philo *phi);
int			eating_count(t_philo *philo);
// error 
void		philo_error(char *error_msg);
// semaphores
void		init_semaphores_bonus(t_data *data);
void		close_semaphores(t_data *data);
#endif