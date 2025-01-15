#include "../philo.h"

static void	assign_forks(t_philo *philo, t_table *table)
{
	if (philo->seat_nbr == 1)
		philo->right_fork = &table->forks[table->no_philos - 1];
	else
		philo->right_fork = &table->forks[philo->seat_nbr - 2];
	philo->left_fork = &table->forks[philo->seat_nbr - 1];
}

void	init_philo(t_philo *philo, t_table *table, int seat_nbr)
{
	philo->id = 0;
	philo->thread = 0;
	philo->table = table;
	philo->seat_nbr = seat_nbr;
	philo->finished_eating = false;
	assign_forks(philo, table);
	philo->time_last_ate = table->start_time;
	pthread_mutex_init(&philo->last_ate_mutex, NULL);
}

t_philo *init_philos(int no_philos, t_table *table)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * no_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < no_philos)
	{
		init_philo(philos + i, table, i + 1);
		i++;
	}
	return (philos);
}

pthread_mutex_t	*init_forks(int count)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * count);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(forks + i, NULL) != 0)
		{
			destroy_mutexes(forks, i - 1);
			free(forks);
			return (NULL);	
		}
		i++;
	}
	return (forks);
}

int	init_table(t_table *table, int argc, char **argv)
{
	table->no_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->no_times_to_eat = 0;
	if (argc == 6)
		table->no_times_to_eat = ft_atoi(argv[5]);
	table->forks = init_forks(table->no_philos);
	if (gettimeofday(&table->start_time, NULL) == -1)
		return (0);
	pthread_mutex_init(&table->print_mutex, NULL);
	return (1);
}

