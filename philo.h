

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				seat_nbr;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	struct timeval	current_time;
	t_table			*table;
}   t_philo;

typedef struct s_table
{
	int				no_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				no_times_to_eat;
	pthread_mutex_t	*forks;
	struct timeval	start_time;
	struct timeval	end_time;
}   t_table;

int		ft_atoi(const char *str);

void	*routine(void *arg);

double	calc_time_diff(struct timeval *start, struct timeval *end);

int 	get_time_stamp(t_philo *philo);

void    take_right_fork(t_philo *philo);

void    take_left_fork(t_philo *philo);

void    eat(t_philo *philo);

void    think(t_philo *philo);

void    sleep(t_philo *philo);

int 	init_philos(int	no_philos, t_table *table);
