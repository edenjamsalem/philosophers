
#include "../philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;

    eat(table, philo);
	sleep(table, philo);
	think(table, philo);
}
