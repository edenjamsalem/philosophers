/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:23:49 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/22 16:42:24 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_table
{
	int				no_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				no_times_to_eat;
	bool			philo_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	died_mutex;
	struct timeval	start_time;
}				t_table;

typedef struct s_philo
{
	pthread_t		thread;
	int				seat_nbr;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_ate_mutex;
	pthread_mutex_t	finished_mutex;
	struct timeval	time_last_ate;
	bool			finished;
	t_table			*table;
}				t_philo;

void			init_philo(t_philo *philo, t_table *table, int seat_nbr);

t_philo			*init_philos(int no_philos, t_table *table);

pthread_mutex_t	*init_forks(int count);

int				init_table(t_table *table, int argc, char **argv);

int				ft_atoi(const char *str);

void			*routine(void *arg);

double			calc_time_diff(struct timeval *start, struct timeval *end);

int				get_time_stamp(t_table *table);

void			eating(t_table *table, t_philo *philo);

void			thinking(t_table *table, t_philo *philo);

void			sleeping(t_table *table, t_philo *philo);

void			run_threads(t_philo *philos, t_table *table);

void			detach_threads(t_table *table, t_philo *philos);

void			destroy_fork_mutexes(pthread_mutex_t *forks, int count);

void			destroy_philo_mutexes(t_philo *philos, int count);

void			print_msg(char *msg, t_table *table, t_philo *philo);

bool			philo_died(t_table *table, t_philo *philos);

bool			threads_finished(t_table *table, t_philo *philos);

bool			access_finished_mutex(t_philo *philo);

bool			access_died_mutex(t_table *table);

void			cleanup(t_table *table, t_philo *philos);

void			monitor_threads(t_table *table, t_philo *philos);

bool			is_dead(t_table *table, t_philo *philo);
