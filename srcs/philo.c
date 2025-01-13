
#include "../philo.h"

int	inputs_are_ints(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("incorrect number of args\n");
		return (0);
	}
	if (!inputs_are_ints(argc, argv))
	{
		printf("args must be integers\n");
		return (0);
	}
	return (1);
}

static bool	is_dead(t_table *table, t_philo *philo)
{
	struct timeval	current_time;
	int				time_since_last_meal;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->last_ate_mutex);
	time_since_last_meal = calc_time_diff(&philo->time_last_ate, &current_time);
	pthread_mutex_unlock(&philo->last_ate_mutex);
	if (time_since_last_meal > table->time_to_die)
		return (1);
	return (0);
}

bool	philo_died(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->no_philos)
	{
		if (is_dead(table, philos + i))
		{
 	        print_msg("died", table, philos + i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;
	t_philo		*philos;

	if (!check_input(argc, argv) || !init_table(&table, argc, argv))
		return (0);
	philos = init_philos(table.no_philos, &table);
	if (!philos)
		return (0);
	run_threads(philos, &table);
	if (!table.no_times_to_eat)
	{
		detach_threads(&table, philos);
		while (!philo_died(&table, philos));
	}
	else
		join_threads(&table, philos);
	destroy_mutexes(table.forks, table.no_philos);
	free(philos);
	free(table.forks);
}
