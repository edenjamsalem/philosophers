/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:22:59 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/22 16:13:00 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	philo_died(t_table *table, t_philo *philos)
{
	int	i;

	if (table->no_philos < 2)
		return (1);
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

bool	threads_finished(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->no_philos && access_finished_mutex(philos + i))
		i++;
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

void	monitor_threads(t_table *table, t_philo *philos)
{
	if (table->no_times_to_eat)
		while (!threads_finished(table, philos) && !philo_died(table, philos))
			usleep(200);
	else
		while (!philo_died(table, philos))
			usleep(200);
}
