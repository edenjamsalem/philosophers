/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:21:55 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/21 17:04:25 by eamsalem         ###   ########.fr       */
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
	exit(IS_FINISHED);
}

void	eat_infinitely(t_table *table, t_philo *philo)
{
	int	no_times_eaten;

	no_times_eaten = 0;
	while (1)
	{
		eating(table, philo);
		sleeping(table, philo);
		thinking(table, philo);
		no_times_eaten++;
	}
}

void	process(t_table *table, t_philo *philo)
{
	pthread_create(&philo->monitor, NULL, check_if_dead, (void *)philo);
	pthread_detach(philo->monitor);
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
/*	if (table->no_philos == 1)
	{
		take_fork(table, philos);
		usleep(table->time_to_die * 1000);
		print_msg("died", table, philos);
		sem_post(table->forks);
		exit(IS_DEAD);
	}*/
	while (i < table->no_philos)
	{
		(philos + i)->pid = ft_fork();
		if ((philos + i)->pid == 0)
		{
			process(table, philos + i);
		}
		pthread_create(&(philos + i)->monitor, NULL, &wait_pids, philos + i);
		pthread_detach((philos + i)->monitor);
		i++;
	}
}
