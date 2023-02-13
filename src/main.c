

#include "../inc/philo.h"

/*
External funct.:

memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/

void	la_grande_bouffe_start(t_data *data, t_philo *philo)
{
	// int	i;

	data->starttime = time_in_ms();
	// printf("%ld\n", data->starttime);
	// i = 0;
	// 	while (i < data->n_philo)
	// {
	// 	if (pthread_create(&data->forks, NULL, &philosopher,
	// 			data->philo[i]) != 0)
	// 		return ;
	// 	i++;
	// }

}


// void	la_grande_bouffe_stop(t_data *data, t_philo *philo)

int	main(int ac, char **av)
{
	t_data *data;
	t_philo *philo;

	if (!valid_input(ac, av))
		return (msg("Input is invalid"), 1);

	data = init_data(ac, av);
	if (!data)
		return(1); // add protected free
	philo = init_philo(data);
	if (!philo)
		return(1); // add protected free
	la_grande_bouffe_start(data, philo);
	//free data
	return(0);
}