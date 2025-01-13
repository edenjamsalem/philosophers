/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:49:15 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/13 17:44:36 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_mutexes(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(forks + i);
		i++;
	}
}

void free_philos(t_table *table, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < table->no_philos)
	{
		free(philos + i);
		i++;
	}
}

void	free_table(t_table *table)
{
	destroy_mutexes(table->forks, table->no_philos);
}