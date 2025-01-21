/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:22:48 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/21 17:04:47 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (*argv[1] == '0')
	{
		printf("must be atleast 1 philosopher\n");
		return (0);
	}
	if (!inputs_are_ints(argc, argv))
	{
		printf("args must be integers\n");
		return (0);
	}
	return (1);
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
	detach_threads(&table, philos);
	if (table.no_times_to_eat)
		while (!philos_finished(&table, philos) && !philo_died(&table, philos))
			usleep(200);
	else
		while (!philo_died(&table, philos))
			usleep(200);
	while (!philos_finished(&table, philos))
		usleep(200);
	destroy_fork_mutexes(table.forks, table.no_philos);
	destroy_philo_mutexes(philos, table.no_philos);
//	pthread_mutex_destroy(&table.died_mutex);
//	pthread_mutex_destroy(&table.print_mutex);
	free(table.forks);
	free(philos);
}
