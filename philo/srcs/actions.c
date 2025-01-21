/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:02:31 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/21 18:46:40 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_fork(pthread_mutex_t *fork, t_table *table, t_philo *philo)
{
	pthread_mutex_lock(fork);
	if (access_died_mutex(table))
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	print_msg("has taken a fork", table, philo);
	return (1);
}

void	eating(t_table *table, t_philo *philo)
{
	if (philo->seat_nbr % 2 != 0)
	{
		if(!take_fork(philo->right_fork, table, philo))
			return ;
		usleep(200);
		if(!take_fork(philo->left_fork, table, philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
	}
	else
	{
		usleep(200);
		if(!take_fork(philo->left_fork, table, philo))
			return ;
		if(!take_fork(philo->right_fork, table, philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			return ;
		}
	}
	print_msg("is eating", table, philo);
	pthread_mutex_lock(&philo->last_ate_mutex);
	gettimeofday(&philo->time_last_ate, NULL);
	pthread_mutex_unlock(&philo->last_ate_mutex);
	usleep(table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	thinking(t_table *table, t_philo *philo)
{
	if (access_died_mutex(table))
		return ;
	print_msg("is thinking", table, philo);
}

void	sleeping(t_table *table, t_philo *philo)
{
	if (access_died_mutex(table))
		return ;
	print_msg("is sleeping", table, philo);
	usleep(philo->table->time_to_sleep * 1000);
}
