/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:22:20 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/18 13:19:21478amsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	take_fork(t_table *table, t_philo *philo)
{
	sem_wait(table->forks);
	print_msg("has taken a fork", table, philo);
}

void	eating(t_table *table, t_philo *philo)
{
	take_fork(table, philo);
	take_fork(table, philo);
	print_msg("is eating", table, philo);
	sem_wait(table->last_ate);
	gettimeofday(&philo->time_last_ate, NULL);
	sem_post(table->last_ate);
	usleep(table->time_to_eat * 1000);
	sem_post(table->forks);
	sem_post(table->forks);
}

void	thinking(t_table *table, t_philo *philo)
{
	print_msg("is thinking", table, philo);
	if (philo->seat_nbr % 2 != 0)
		usleep(1000);
}

void	sleeping(t_table *table, t_philo *philo)
{
	print_msg("is sleeping", table, philo);
	usleep(table->time_to_sleep * 1000);
}
