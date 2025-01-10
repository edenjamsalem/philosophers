
#include "../philo.h"

int	check_int_input(int argc, char **argv)
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
		printf("incorrect number of args");
		return (0);
	}
	if (!check_int_input(argc, argv))
	{
		printf("args must be integers");
		return (0);
	}
	return (1);
}

void	cleanup_mutexes(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(forks + i);
		i++;
	}
}

void	run_infinitely(t_philo *philos, t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->no_philos)
		{
			pthread_create((philos + i)->thread, NULL, routine(philos + i), );
			i++;
		}

	}
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
	if (!table.no_times_to_eat)
		run_infinitely(philos, &table);
	else
		run_until_finished(philos, &table);
}
