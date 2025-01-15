/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:01:51 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/15 15:02:17 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	is_dead(t_table *table, t_philo *philo)
{
	struct timeval	current_time;
	int				time_since_last_meal;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->last_ate_mutex);
	time_since_last_meal = calc_time_diff(&philo->time_last_ate, &current_time);
	pthread_mutex_unlock(&philo->last_ate_mutex);
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
		if (is_dead(table, philos + i))
		{
 	        print_msg("died", table, philos + i);
			return (1);
		}
		i++;
	}
	return (0);
}

bool	philos_finished(t_table *table, t_philo *philos)
{
	int	i;
	int	finished_count;

	i = 0;
	finished_count = 0;
	while (i < table->no_philos)
	{
		if ((philos + i)->finished_eating)
			finished_count++;
		i++;
	}
	if (finished_count == table->no_philos)	
		return (1);
	return (0);
}