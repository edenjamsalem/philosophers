/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:50:26 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/29 14:17:44 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat_until_finished(t_table *table, t_philo *philo)
{
	int	no_times_eaten;

	no_times_eaten = 0;
	while (!access_died_mutex(table) && no_times_eaten < table->no_times_to_eat)
	{
		eating(table, philo);
		sleeping(table, philo);
		thinking(table, philo);
		no_times_eaten++;
	}
	pthread_mutex_lock(&philo->finished_mutex);
	philo->finished = true;
	pthread_mutex_unlock(&philo->finished_mutex);
}

void	eat_infinitely(t_table *table, t_philo *philo)
{
	while (!access_died_mutex(table))
	{
		eating(table, philo);
		sleeping(table, philo);
		thinking(table, philo);
	}
	pthread_mutex_lock(&philo->finished_mutex);
	philo->finished = true;
	pthread_mutex_unlock(&philo->finished_mutex);
}

void	handle_single_philo(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_msg("has taken a fork", table, philo);
	usleep((table->time_to_die) * 1000);
	print_msg("died", table, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->finished_mutex);
	philo->finished = true;
	pthread_mutex_unlock(&philo->finished_mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (table->no_philos == 1)
	{
		handle_single_philo(table, philo);
		return (NULL);
	}
	if (philo->seat_nbr % 2 != 0)
		usleep(table->time_to_eat * 1000);
	if (!table->no_times_to_eat)
		eat_infinitely(table, philo);
	else
		eat_until_finished(table, philo);
	return (NULL);
}
