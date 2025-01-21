/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:22:59 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/21 15:22:21 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	is_dead(t_table *table, t_philo *philo)
{
	struct timeval	current_time;
	struct timeval	time_last_ate;
	int				time_since_last_meal;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->last_ate_mutex);
	time_last_ate = philo->time_last_ate;
	pthread_mutex_unlock(&philo->last_ate_mutex);
	time_since_last_meal = calc_time_diff(&time_last_ate, &current_time);
	if (time_since_last_meal > table->time_to_die)
		return (1);
	return (0);
}

bool	philo_died(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->no_philos)
	{
		if (is_dead(table, philos + i) && !access_finished_mutex(philos + i))
		{
			print_msg("died", table, philos + i);
			pthread_mutex_lock(&table->died_mutex);
			table->philo_died = true;
			pthread_mutex_unlock(&table->died_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

bool	philos_finished(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (access_finished_mutex(philos + i))
	{
		i++;
	}
	if (i == table->no_philos)
		return (1);
	return (0);
}

bool	access_finished_mutex(t_philo *philo)
{
	bool	finished;

	pthread_mutex_lock(&philo->finished_mutex);
	finished = philo->finished;
	pthread_mutex_unlock(&philo->finished_mutex);
	return (finished);
}

bool	access_died_mutex(t_table *table)
{
	bool	philo_died;

	pthread_mutex_lock(&table->died_mutex);
	philo_died = table->philo_died;
	pthread_mutex_unlock(&table->died_mutex);
	return (philo_died);
}
