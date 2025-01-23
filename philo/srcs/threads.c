/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:22:36 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/23 12:40:11 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	run_threads(t_philo *philos, t_table *table)
{
	pthread_t	*thread;
	int			i;

	i = 0;
	while (i < table->no_philos)
	{
		thread = &((philos + i)->thread);
		pthread_create(thread, NULL, &routine, (void *)(philos + i));
		i++;
	}
}

void	detach_threads(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->no_philos)
	{
		pthread_detach((philos + i)->thread);
		i++;
	}
}

void	join_threads(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->no_philos)
	{
		pthread_join((philos + i)->thread, NULL);
		i++;
	}
}

void	wait_for_threads_to_close(t_table *table, t_philo *philos)
{
	usleep(1000);
	while (!threads_finished(table, philos))
		usleep(500);
}
