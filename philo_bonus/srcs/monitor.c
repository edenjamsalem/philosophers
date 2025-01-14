
#include "../philo_bonus.h"

bool	is_dead(t_table *table, t_philo *philo)
{
	struct timeval	current_time;
	int				time_since_last_meal;

	gettimeofday(&current_time, NULL);
	time_since_last_meal = calc_time_diff(&philo->time_last_ate, &current_time);
	if (time_since_last_meal > table->time_to_die)
		return (1);
	return (0);
}

void	*check_if_dead(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (!is_dead(philo->table, philo))
		usleep(1000);
    cleanup_table(philo->table);
	exit(1);
}

static int	monitor_child_processes(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while ((philos + i)->status == -1)
		i++;
	if (i == table->no_philos)
		return (0);
	else if (WIFEXITED((philos + i)->status))
	{
		(philos + i)->is_dead = WEXITSTATUS((philos + i)->status);
		if ((philos + i)->is_dead)
		{
			kill_children(table, philos);
			print_msg("died", table, philos + i);
			return (-1);
		}
		(philos + i)->status = -1;
		return (1);
	}	
	return (0);
}

bool	processes_running(t_table *table, t_philo *philos)
{
	int	finished_count;
	int	exit_status;

	finished_count = 0;
	while (finished_count < table->no_philos)
	{
		exit_status = monitor_child_processes(table, philos);
		if (exit_status == -1)
			return (0); 
		finished_count += exit_status;
	}
	return (0);
}

bool	philo_died(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->no_philos)
	{
		if ((philos + i)->status)
		{
			if (WIFEXITED((philos + i)->status))
				(philos + i)->is_dead = WEXITSTATUS((philos + i)->status);
			if ((philos + i)->is_dead)
			{
				kill_children(table, philos);
				print_msg("died", table, philos + i);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
