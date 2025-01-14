/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:03:41 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/14 17:52:08 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void take_fork(t_table *table, t_philo *philo)
{
    sem_wait(table->forks);
    print_msg("has taken a fork", table, philo);
}

void    eating(t_table *table, t_philo *philo)
{
    take_fork(table, philo);
    take_fork(table, philo);
    print_msg("is eating", table, philo);
	usleep(table->time_to_eat * 1000);
    sem_post(table->forks);
    sem_post(table->forks);
	gettimeofday(&philo->time_last_ate, NULL);
}

void    thinking(t_table *table, t_philo *philo)
{
    print_msg("is thinking", table, philo);
}

void    sleeping(t_table *table, t_philo *philo)
{
    print_msg("is sleeping", table, philo);
    usleep(table->time_to_sleep * 1000);
}
