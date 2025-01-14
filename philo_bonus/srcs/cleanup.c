
#include "../philo_bonus.h"

void	cleanup_table(t_table *table)
{
	sem_close(table->forks);
	sem_unlink("/forks");
	sem_close(table->print_sem);
	sem_unlink("/print");
	free(table->child_pids);
	free(table->child_status);
}


void	kill_children(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philos)
	{
		kill(table->child_pids[i], SIGKILL);
		i++;
	}
}
