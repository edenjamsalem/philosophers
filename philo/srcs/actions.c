/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:23:04 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/15 15:30:15 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(pthread_mutex_t *fork, t_table *table, t_philo *philo)
{
	pthread_mutex_lock(fork);
	print_msg("has taken a fork", table, philo);
}

void	eating(t_table *table, t_philo *philo)
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
	pthread_mutex_lock(&philo->last_ate_mutex);
	gettimeofday(&philo->time_last_ate, NULL);
	pthread_mutex_unlock(&philo->last_ate_mutex);
}

void	thinking(t_table *table, t_philo *philo)
{
	print_msg("is thinking", table, philo);
}

void	sleeping(t_table *table, t_philo *philo)
{
	print_msg("is sleeping", table, philo);
	usleep(philo->table->time_to_sleep * 1000);
}
