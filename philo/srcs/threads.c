/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:22:36 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/15 15:27:37 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	run_threads(t_philo *philos, t_table *table)
{
	pthread_t	*thread;
	int			*id;
	int			i;

	i = 0;
	while (i < table->no_philos)
	{
		thread = &((philos + i)->thread);
		id = &((philos + i)->id);
		*id = pthread_create(thread, NULL, &routine, (void *)(philos + i));
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
