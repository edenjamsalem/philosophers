
#include "../philo_bonus.h"

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

void	wait_for_pids(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->no_philos)
	{
		waitpid((philos + i)->pid, &(philos + i)->status, 0);
		i++;
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
	run_processes(philos, &table);
	wait_for_pids(&table, philos);
	if (!table.no_times_to_eat)
	{
		while (!philo_died(&table, philos));
	}
	else
	{
		while (processes_running(&table, philos));
	}
	cleanup_table(&table);
	free(philos);
}
