/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:22:59 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/16 16:44:57 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	is_dead(t_table *table, t_philo *philo)
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

	i = -1;
	while (++i < table->no_philos)
	{
		if (is_dead(table, philos + i) && !finished_eating(philos + i))
		{
			print_msg("died", table, philos + i);
			return (1);
		}
	}
	return (0);
}

bool	philos_finished(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (finished_eating(philos + i))
		i++;
	if (i == table->no_philos)
		return (1);
	return (0);
}

bool	finished_eating(t_philo *philo)
{
	bool finished;
	
	pthread_mutex_lock(&philo->finished_mutex);
	finished = philo->finished_eating;
	pthread_mutex_unlock(&philo->finished_mutex);
	return (finished);
}
