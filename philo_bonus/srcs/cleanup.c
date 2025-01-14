
#include "../philo_bonus.h"

void	cleanup_table(t_table *table)
{
	sem_close(table->forks);
	sem_unlink("/forks");
	sem_close(table->print_sem);
	sem_unlink("/print");
}

void	kill_children(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->no_philos)
	{
		kill((philos + i)->pid, SIGTERM);
		i++;
	}
}
