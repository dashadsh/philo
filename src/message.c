
#include "../inc/philo.h"

void	red(void)
{
	printf("\033[1;31m");
}

void	msg(char *s)
{
	red();
	printf("%s\n", s);
}

void	print_status(t_philo *philo, char *s)
{
	pthread_mutex_lock(&(philo->data->write_lock));
	if (!(sim_stop(philo, 0)))
	{
		printf("%ld ", time_in_ms() - philo->data->starttime);
		printf("%i ", philo->id + 1);
		printf("%s\n", s);
	}
	pthread_mutex_unlock(&(philo->data->write_lock));
}
