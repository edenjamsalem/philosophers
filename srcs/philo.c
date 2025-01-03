
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

int	init_table(t_table *table, int argc, char **argv)
{
	table->no_philos = ft_atoi(argv[0]);
	table->time_to_die = ft_atoi(argv[1]);
	table->time_to_eat = ft_atoi(argv[2]);
	table->time_to_sleep = ft_atoi(argv[3]);
	table->no_times_to_eat = 0;
	if (argc == 5)
		table->no_times_to_eat = ft_atoi(argv[3]);
	if (gettimeofday(&table->start_time, NULL) == -1)
		return (0);
	return (1);
}

double	calc_time(struct timeval *start, struct timeval *end)
{
	time_t secs;
	suseconds_t micro_secs;

	secs = end->tv_sec - start->tv_sec;
	micro_secs = end->tv_usec - start->tv_usec;
	if (micro_secs < 0)
	{
		micro_secs += 1000000;
		secs--;
	}
	return ((double)secs + (double)micro_secs / 1000000.0);
}


int	main(int argc, char **argv)
{
	t_table table;
	double	time_elapsed;

	if (!check_input(argc, argv) || !init_table(&table, argc, argv))
		return (0);
	sleep(1);
	gettimeofday(&table.end_time, NULL);
	time_elapsed = calc_time(&table.start_time, &table.end_time);
	printf("%f\n", time_elapsed);
}