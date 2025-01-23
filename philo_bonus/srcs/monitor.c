/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:21:59 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/23 12:51:35 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

bool	is_dead(t_table *table, t_philo *philo)
{
	struct timeval	current_time;
	struct timeval	time_last_ate;
	int				time_since_last_meal;

	gettimeofday(&current_time, NULL);
	sem_wait(table->last_ate);
	time_last_ate = philo->time_last_ate;
	sem_post(table->last_ate);
	time_since_last_meal = calc_time_diff(&time_last_ate, &current_time);
	if (time_since_last_meal > table->time_to_die)
		return (1);
	return (0);
}

void	*check_if_dead(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (!is_dead(philo->table, philo))
		usleep(1000);
	print_msg("died", table, philo);
	exit(IS_DEAD);
}

void	*wait_pids(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	int		exit_status;

	philo = (t_philo *)arg;
	table = philo->table;
	waitpid(philo->pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
	{
		sem_wait(table->status_sem);
		philo->status = WEXITSTATUS(exit_status);
		sem_post(table->status_sem);
	}
	return (NULL);
}

int	processes_running(t_table *table, t_philo *philos)
{
	int	i;
	int	finished_count;
	int	status;

	i = 0;
	finished_count = 0;
	while (i < table->no_philos)
	{
		sem_wait(table->status_sem);
		status = (philos + i)->status;
		sem_post(table->status_sem);
		if (status == IS_FINISHED)
			finished_count++;
		else if (status == IS_DEAD)
		{
			kill_children(table, philos);
			sem_post(table->print_sem);
			return (0);
		}
		i++;
	}
	if (finished_count == table->no_philos)
		return (0);
	return (1);
}
