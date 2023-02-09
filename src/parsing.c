
#include "../inc/philo.h"

// struct timeval {
//    time_t      tv_sec;   // Number of whole seconds of elapsed time
//    long int    tv_usec;  // Number of microseconds of rest of elapsed time minus tv_sec.
// }


// Returns the timestamp in milliseconds
   //1 sec = 1000000 microsecond
   //1 sec = 1000 millisec
   //1 millisec = 1000 microsec
   
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
	data->n_must_eat = -1;
	if (ac == 6)
		data->n_must_eat = philo_atoi(av[5]);
 //add sim_stop_flag
}