/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:22:29 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/22 16:28:38 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		nbr_int;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	nbr_int = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr_int *= 10;
		nbr_int += str[i] - '0';
		i++;
	}
	return (nbr_int * sign);
}

void	print_msg(char *msg, t_table *table, t_philo *philo)
{
	int	time_stamp;

	time_stamp = get_time_stamp(table);
	pthread_mutex_lock(&table->print_mutex);
	printf("%d %d %s\n", time_stamp, philo->seat_nbr, msg);
	pthread_mutex_unlock(&table->print_mutex);
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

bool	is_dead(t_table *table, t_philo *philo)
{
	struct timeval	current_time;
	struct timeval	time_last_ate;
	int				time_since_last_meal;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->last_ate_mutex);
	time_last_ate = philo->time_last_ate;
	pthread_mutex_unlock(&philo->last_ate_mutex);
	time_since_last_meal = calc_time_diff(&time_last_ate, &current_time);
	if (time_since_last_meal > table->time_to_die)
		return (1);
	return (0);
}
