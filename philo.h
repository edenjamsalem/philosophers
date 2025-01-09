

#include <stdio.h>
#include <stdlib.h>
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
	int				*forks;
	struct timeval	start_time;
	struct timeval	end_time;
}   t_table;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;

}   t_philo;

int		ft_atoi(const char *str);

