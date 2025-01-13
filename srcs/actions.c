/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:03:41 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/13 17:46:32 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    take_fork(pthread_mutex_t *fork, t_table *table, t_philo *philo)
{
    pthread_mutex_lock(fork);
    print_msg("has taken a fork", table, philo);
}

void    eating(t_table *table, t_philo *philo)
{
    if (philo->seat_nbr % 2 == 0)
    {
        take_fork(philo->right_fork, table, philo);
        take_fork(philo->left_fork, table, philo);
    }
    else
    {
        take_fork(philo->left_fork, table, philo);
        take_fork(philo->right_fork, table, philo);
    }
	
    print_msg("is eating", table, philo);
	usleep(table->time_to_eat * 1000);
	
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	
	// CHECK IF I NEED THIS MUTEX
//	pthread_mutex_lock(&philo->last_ate_mutex);
	gettimeofday(&philo->time_last_ate, NULL);
//	pthread_mutex_unlock(&philo->last_ate_mutex);
}

void    thinking(t_table *table, t_philo *philo)
{
    print_msg("is thinking", table, philo);
}

void    sleeping(t_table *table, t_philo *philo)
{
    print_msg("is sleeping", table, philo);
    usleep(philo->table->time_to_sleep * 1000);
}
