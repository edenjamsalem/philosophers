/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:22:12 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/15 15:22:15 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	cleanup_table(t_table *table)
{
	sem_close(table->forks);
	sem_unlink("/forks");
	sem_close(table->print_sem);
	sem_unlink("/print");
}

void	kill_children(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->no_philos)
	{
		kill((philos + i)->pid, SIGTERM);
		i++;
	}
}
