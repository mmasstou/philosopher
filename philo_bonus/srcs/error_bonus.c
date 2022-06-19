#include "../philo_bonus.h"

void    philo_error(char *error_msg, int type)
{
    (void)type;
    ft_putendl_fd(error_msg, STDERR_FILENO);;
    system("leaks philo");
    exit(1);
}