/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:10:33 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/22 16:48:40 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_fork_mutexes(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(forks + i);
		i++;
	}
}

void	destroy_philo_mutexes(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&(philos + i)->finished_mutex);
		pthread_mutex_destroy(&(philos + i)->last_ate_mutex);
		i++;
	}
}

void	cleanup(t_table *table, t_philo *philos)
{
	destroy_fork_mutexes(table->forks, table->no_philos);
	destroy_philo_mutexes(philos, table->no_philos);
	pthread_mutex_destroy(&table->died_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(philos);
}
