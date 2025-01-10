

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
	pthread_mutex_t	*forks;
	struct timeval	start_time;
}   t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				seat_nbr;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	current_time;
	t_table			*table;
}   t_philo;

void			init_philo(t_philo *philo, t_table *table, int seat_nbr);

t_philo			*init_philos(int no_philos, t_table *table);

pthread_mutex_t	*init_forks(int count);

int				init_table(t_table *table, int argc, char **argv);

int				ft_atoi(const char *str);

void			*routine(void *arg);

double			calc_time_diff(struct timeval *start, struct timeval *end);

int				get_time_stamp(t_table *table, t_philo *philo);

void			take_right_fork(t_table *table, t_philo *philo);

void			take_left_fork(t_table *table, t_philo *philo);

void			eating(t_table *table, t_philo *philo);

void			thinking(t_table *table, t_philo *philo);

void			sleeping(t_table *table, t_philo *philo);

void			run_threads(t_philo *philos, t_table *table);

void			join_threads(t_table *table, t_philo *philos);

void			detach_threads(t_table *table, t_philo *philos);

void	 		free_philos(t_table *table, t_philo *philos);

void			free_table(t_table *table);

void			destroy_mutexes(pthread_mutex_t *forks, int count);

void			print_msg(char *msg, t_table *table, t_philo *philo);
