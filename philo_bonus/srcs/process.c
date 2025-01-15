/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:21:55 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/15 15:33:12 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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
	exit(0);
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

void	process(t_table *table, t_philo *philo)
{
	pthread_create(&philo->monitor, NULL, check_if_dead, (void *)philo);
	pthread_detach(philo->monitor);
	if (philo->seat_nbr % 2 == 0)
		usleep(1000);
	if (!table->no_times_to_eat)
		eat_infinitely(table, philo);
	else
		eat_until_finished(table, philo);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	run_processes(t_philo *philos, t_table *table)
{
	int			i;

	i = 0;
	while (i < table->no_philos)
	{
		(philos + i)->pid = ft_fork();
		if ((philos + i)->pid == 0)
		{
			process(table, philos + i);
		}
		i++;
	}
}
