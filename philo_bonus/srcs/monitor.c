
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
