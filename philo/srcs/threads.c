/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:14:35 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/13 17:45:39 by eamsalem         ###   ########.fr       */
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
