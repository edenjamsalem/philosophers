/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:02:31 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/22 16:46:28 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	take_right_then_left(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (access_died_mutex(table))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_msg("has taken a fork", table, philo);
	usleep(200);
	pthread_mutex_lock(philo->left_fork);
	if (access_died_mutex(table))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_msg("has taken a fork", table, philo);
	return (0);
}

bool	take_left_then_right(t_table *table, t_philo *philo)
{
	usleep(200);
	pthread_mutex_lock(philo->left_fork);
	if (access_died_mutex(table))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_msg("has taken a fork", table, philo);
	pthread_mutex_lock(philo->right_fork);
	if (access_died_mutex(table))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_msg("has taken a fork", table, philo);
	return (0);
}

void	eating(t_table *table, t_philo *philo)
{
	bool	died_waiting;

	if (philo->seat_nbr % 2 != 0)
		died_waiting = take_right_then_left(table, philo);
	else
		died_waiting = take_left_then_right(table, philo);
	if (died_waiting)
		return ;
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
