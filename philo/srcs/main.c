/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:22:48 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/22 15:45:04 by eamsalem         ###   ########.fr       */
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

void wait_for_threads_to_close(t_table *table, t_philo *philos)
{
	while (!threads_finished(table, philos))
		usleep(500);
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
	monitor_threads(&table, philos);
	wait_for_threads_to_close(&table, philos);
	cleanup(&table, philos);
}
