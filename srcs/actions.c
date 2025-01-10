
#include "../philo.h"

void    take_right_fork(t_table *table, t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    print_msg("has taken a fork", table, philo);
}

void    take_left_fork(t_table *table, t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_msg("has taken a fork", table, philo);
}

void    eating(t_table *table, t_philo *philo)
{
    if (philo->seat_nbr % 2 == 0)
    {
        take_right_fork(table, philo);
        take_left_fork(table, philo);
    }
    else
    {
        take_left_fork(table, philo);
        take_right_fork(table, philo);
    }
    print_msg("is eating", table, philo);
	usleep(table->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void    thinking(t_table *table, t_philo *philo)
{
    print_msg("is thinking", table, philo);
}

void    sleeping(t_table *table, t_philo *philo)
{
    print_msg("is sleeping", table, philo);
    usleep(philo->table->time_to_sleep);
}
