#include "philo_bonus.h"


t_philo *init_philos_bonus(t_data *data)
{
    t_philo *philo;
    int     i;

    i = 0;
    philo = NULL;
    data->simulation_ended = 0;
    while (++i <= data->args.number_of_philosophers)
        add_back(&philo, lstnew(i, data));
    data->head = philo;
    return (philo);
}

void    f()
{
    system("leaks philo");
}

int main(int argc, char *argv[])
{
    t_data  data;
    t_philo *philo;
    t_philo *temp;

    // atexit(f);
    if ((argc < 5 ||  argc > 6))
        philo_error("Error", 0);
    ft_parse_bonus(argc, argv + 1, &data.args);
    philo = init_philos_bonus(&data);
    if (!philo)
        return (1);
    init_semaphores_bonus(&data);
    data.simulation_start = get_time();
     _starting_bonus(philo);
    while (philo)
    {
        temp = philo->next;
        free(philo);
        philo = temp;
    }
    data.head = NULL;
    philo = NULL;
    return (0);
}