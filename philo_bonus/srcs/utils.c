/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:21:44 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/20 14:32:52 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_size;
	size_t	src_size;

	dest_size = ft_strlen(dest);
	src_size = ft_strlen(src);
	if (size <= dest_size)
		return (src_size + size);
	i = dest_size;
	j = 0;
	while (src[j] && i < (size - 1))
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest_size + src_size);
}

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

char	*ft_itoa(char *str, int nbr)
{
	char	tmp[4];
	int		i;

	i = 0;
	while (nbr != 0)
	{
		tmp[i] = (nbr % 10) + '0';
		nbr /= 10;
		i++;
	}
	str[i] = '\0';
	while (--i >= 0)
		str[i] = tmp[i];
	return (str);
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
