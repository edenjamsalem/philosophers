
#include "../philo.h"

double	calc_time_diff(struct timeval *start, struct timeval *end)
{
	time_t secs;
	time_t millisecs;
	suseconds_t micro_secs;

	secs = end->tv_sec - start->tv_sec;
	micro_secs = end->tv_usec - start->tv_usec;
	if (micro_secs < 0)
	{
		micro_secs += 1000000;
		secs--;
	}
	millisecs =((double)secs + (double)micro_secs / 1000000.0) * 1000; 
	return (millisecs);
}

int get_time_stamp(t_table *table)
{
    float 			time_stamp;
	struct timeval	current_time;

    gettimeofday(&current_time, NULL);
    time_stamp = calc_time_diff(&table->start_time, &current_time);
	return (time_stamp);
}
