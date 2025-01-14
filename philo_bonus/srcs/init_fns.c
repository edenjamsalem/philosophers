#include "../philo_bonus.h"

void	init_philo(t_philo *philo, t_table *table, int seat_nbr)
{
	philo->seat_nbr = seat_nbr;
	philo->time_last_ate = table->start_time;
	philo->table = table;
	philo->status = -1;
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

int	init_table(t_table *table, int argc, char **argv)
{
	table->no_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->no_times_to_eat = 0;
	table->forks = sem_open("/forks", O_CREAT, 0444, table->no_philos);
	table->print_sem = sem_open("/print", O_CREAT, 0444, 1);
	if (argc == 6)
		table->no_times_to_eat = ft_atoi(argv[5]);
	if (gettimeofday(&table->start_time, NULL) == -1)
		return (0);
	return (1);
}

