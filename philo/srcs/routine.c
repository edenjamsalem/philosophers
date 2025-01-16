/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:22:42 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/16 15:58:59 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat_until_finished(t_table *table, t_philo *philo)
{
	int	no_times_eaten;

	no_times_eaten = 0;
	while (no_times_eaten < table->no_times_to_eat)
	{
		eating(table, philo);
		sleeping(table, philo);
		thinking(table, philo);
		no_times_eaten++;
	}
	pthread_mutex_lock(&philo->finished_mutex);
	philo->finished_eating = true;
	pthread_mutex_unlock(&philo->finished_mutex);
}

void	eat_infinitely(t_table *table, t_philo *philo)
{
	while (1)
	{
		eating(table, philo);
		sleeping(table, philo);
		thinking(table, philo);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (table->no_philos == 1)
	{
		take_fork(philo->right_fork, table, philo);
		usleep((table->time_to_die + 1) * 1000);
		return (NULL);
	}
	if (!table->no_times_to_eat)
		eat_infinitely(table, philo);
	else
		eat_until_finished(table, philo);
	return (NULL);
}
