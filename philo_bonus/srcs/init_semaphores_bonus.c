#include "../philo_bonus.h"

void	close_semaphores(t_data *data)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_EAT);
	sem_unlink(SEM_WIRTE);
	sem_close(data->fork);
	sem_close(data->eating);
	sem_close(data->wirteing);
}

void    init_semaphores_bonus(t_data *data)
{
    printf("+++> %d\n",data->args.number_of_philosophers);
    data->fork = sem_open(SEM_FORK, O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR, data->args.number_of_philosophers);
    if (data->fork == SEM_FAILED)
    {
        sem_unlink(SEM_FORK);
        data->fork = sem_open(SEM_FORK, O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR, data->args.number_of_philosophers);
        if (data->fork == SEM_FAILED)
            philo_error("can't create fork semphores !", 1);
    }
    data->eating = sem_open(SEM_EAT, O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR, 1);
    if (data->eating == SEM_FAILED)
    {
        sem_unlink(SEM_EAT);
       data->eating = sem_open(SEM_EAT, O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR, 1);
        if (data->eating == SEM_FAILED)
        {
            sem_unlink(SEM_FORK);
            sem_close(data->fork);
            philo_error("can't create eating  semphore !", 1);
        }
    }
    data->wirteing = sem_open(SEM_WIRTE, O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR, 1);
    if (data->wirteing == SEM_FAILED)
    {
        sem_unlink(SEM_WIRTE);
        data->wirteing = sem_open(SEM_WIRTE, O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR, 1);
        if (data->wirteing == SEM_FAILED)
        {
            sem_unlink(SEM_FORK);
            sem_close(data->fork);
            sem_unlink(SEM_EAT);
            sem_close(data->eating);
            philo_error("can't create wirteing semphore !", 1);
        }
    }
}