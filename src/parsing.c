
#include "../inc/philo.h"

void extract_starttime(t_data *data)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	data->starttime = t.tv_sec * 1000 + t.tv_usec / 1000;
	//printf("%ld\n", data->starttime);
}

void extract_args(t_data *data, int ac, char **av)
{
	data->n_philo = philo_atoi(av[1]);
	data->time_to_die = philo_atoi(av[2]);
	data->time_to_eat = philo_atoi(av[3]);
	data->time_to_sleep = philo_atoi(av[4]);
	data->n_to_eat = -1;
	if (ac == 6)
		data->n_to_eat = philo_atoi(av[5]);
 //add sim_stop_flag
}