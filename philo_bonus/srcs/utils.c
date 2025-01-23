/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:21:44 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/23 12:51:10 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		nbr_int;

	i = 0;
	nbr_int = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr_int *= 10;
		nbr_int += str[i] - '0';
		i++;
	}
	return (nbr_int);
}

void	print_msg(char *msg, t_table *table, t_philo *philo)
{
	sem_wait(table->print_sem);
	printf("%d %d %s\n", get_time_stamp(table), philo->seat_nbr, msg);
	if (*msg != 'd')
		sem_post(table->print_sem);
}

double	calc_time_diff(struct timeval *start, struct timeval *end)
{
	time_t		secs;
	time_t		millisecs;
	suseconds_t	micro_secs;

	secs = end->tv_sec - start->tv_sec;
	micro_secs = end->tv_usec - start->tv_usec;
	if (micro_secs < 0)
	{
		micro_secs += 1000000;
		secs--;
	}
	millisecs = ((double)secs + (double)micro_secs / 1000000.0) * 1000;
	return (millisecs);
}

int	get_time_stamp(t_table *table)
{
	float			time_stamp;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time_stamp = calc_time_diff(&table->start_time, &current_time);
	return (time_stamp);
}
