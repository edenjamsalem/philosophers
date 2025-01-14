
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

bool	philo_died(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->no_philos)
	{
		if (table->child_status[i] != -1)
		{
			if (table->child_status && WIFEXITED(table->child_status[i]))
				(philos + i)->is_dead = WEXITSTATUS(table->child_status[i]);
			if ((philos + i)->is_dead)
			{
				kill_children(table);
				print_msg("died", table, philos + i);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

bool	check_process_finished(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->no_philos)
	{
		if (table->child_status[i] != -1)
		{
			if (WIFEXITED(table->child_status[i]))
			{
				(philos + i)->is_dead = WEXITSTATUS(table->child_status[i]);
				if ((philos + i)->is_dead)
				{
					kill_children(table);
					print_msg("died", table, philos + i);
				}
				table->child_status[i] = -1;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

bool	processes_running(t_table *table, t_philo *philos)
{
	int	finished_count;

	finished_count = 0;
	while (finished_count < table->no_philos)
	{
		finished_count += check_process_finished(table, philos);
	}
	return (0);
}

void	wait_for_pids(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philos)
	{
		waitpid(table->child_pids[i], table->child_status + i, 0);
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
	wait_for_pids(&table);
	if (!table.no_times_to_eat)
	{
		while (!philo_died(&table, philos));
	}
	else
	{
		while(processes_running(&table, philos));
	}
	cleanup_table(&table);
	free(philos);
}
