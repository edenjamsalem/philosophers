/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:03:41 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/10 17:34:11 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool    philo_died(t_table *table, t_philo *philo)
{
	struct timeval	current_time;
	double			time_without_eating;	

	gettimeofday(&current_time, NULL);
	time_without_eating = calc_time_diff(&philo->time_last_ate, &current_time); 
	if (time_without_eating > table->time_to_die)
		return (1);
	return (0);
}

bool    take_fork(pthread_mutex_t *fork, t_table *table, t_philo *philo)
{
    pthread_mutex_lock(fork);
    if (philo_died(table, philo))
    {
		pthread_mutex_unlock(fork);
        print_msg("died", table, philo);
		return (0);
    }
    print_msg("has taken a fork", table, philo);
	return (1);
}

bool    eating(t_table *table, t_philo *philo)
{
    if (philo->seat_nbr % 2 == 0)
    {
        if (!take_fork(philo->right_fork, table, philo))
			return (0);
        if(!take_fork(philo->left_fork, table, philo))
			return (0);
    }
    else
    {
        if(!take_fork(philo->left_fork, table, philo))
			return (0);
        if (!take_fork(philo->right_fork, table, philo))
			return (0);
    }
    print_msg("is eating", table, philo);
	usleep(table->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	gettimeofday(&philo->time_last_ate, NULL);
	return (1);
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
