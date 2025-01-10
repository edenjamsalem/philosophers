
#include "../philo.h"

double	calc_time_diff(struct timeval *start, struct timeval *end)
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

int get_time_stamp(t_table *table, t_philo *philo)
{
    float  time_stamp;

    gettimeofday(&philo->current_time, NULL);
    time_stamp = calc_time_diff(&table->start_time, &philo->current_time);
    return (time_stamp * 1000);
}
