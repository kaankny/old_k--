#include <sys/time.h>

static double start_time;

double get_time()
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	return current_time.tv_sec * 1000 + current_time.tv_usec / 1000.0;
}

void	start_timer()
{
	start_time = get_time();
}

double	get_time_elapsed()
{
	double end_time = get_time();
	return (end_time - start_time);
}
