

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <semaphore.h>

typedef struct s_table
{
	int				no_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				no_times_to_eat;
	sem_t			*forks;
	sem_t			*print_sem;
	struct timeval	start_time;
	pid_t			*child_pids;
	pid_t			*child_status;
}   t_table;

typedef struct s_philo
{
	int				seat_nbr;
	struct timeval	time_last_ate;
	t_table			*table;
	int				is_dead;
	pthread_t		monitor;
}   t_philo;

void			init_philo(t_philo *philo, t_table *table, int seat_nbr);

t_philo			*init_philos(int no_philos, t_table *table);

int				init_table(t_table *table, int argc, char **argv);

int				ft_atoi(const char *str);

void			process(t_table *table, t_philo *philo);

double			calc_time_diff(struct timeval *start, struct timeval *end);

int				get_time_stamp(t_table *table);

void			eating(t_table *table, t_philo *philo);

void			thinking(t_table *table, t_philo *philo);

void			sleeping(t_table *table, t_philo *philo);

void			run_processes(t_philo *philos, t_table *table);

void			destroy_mutexes(pthread_mutex_t *forks, int count);

void			print_msg(char *msg, t_table *table, t_philo *philo);

bool			philo_died(t_table *table, t_philo *philos);

void			cleanup_table(t_table *table);

bool			is_dead(t_table *table, t_philo *philo);

void			*check_if_dead(void *arg);

void			kill_children(t_table *table);
