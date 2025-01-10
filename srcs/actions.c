
#include "../philo.h"

void    take_right_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->right_fork);
    printf("%d %d has taken a fork\n", get_time_stamp(philo), philo->seat_nbr);
}

void    take_left_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_fork);
    printf("%d %d has taken a fork\n", get_time_stamp(philo), philo->seat_nbr);
}

void    eat(t_philo *philo)
{
    if (philo->seat_nbr % 2 == 0)
    {
        take_right_fork(philo);
        take_left_fork(philo);
    }
    else
    {
        take_left_fork(philo);
        take_right_fork(philo);
    }
    printf("%d %d is eating\n", get_time_stamp(philo), philo->seat_nbr);
	usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void    think(t_philo *philo)
{
    printf("%d %d is thinking", get_time_stamp(philo), philo->seat_nbr);
}

void    sleep(t_philo *philo)
{
    printf("%d %d is sleeping", get_time_stamp(philo), philo->seat_nbr);
    usleep(philo->table->time_to_sleep);
}

