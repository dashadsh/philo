

#include "../inc/philo.h"

/*
External funct.:

memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/


// void	print_status(t_philo *philo, char *s)
// {
// 	printf("%ld philo #%d %s\n", time_in_ms() - philo->data->starttime, \
// 			philo_struct->id + 1, s);
// }


void	*one_philo_routine(t_philo *philo)
{
	t_data *data;
	printf("%d philo #1 died\n", philo->data->time_to_die);
	// printf("I'M LONELY!\n");
	return (NULL);
}


void	*philo_routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	// printf("%d\n", philo->data->n_philo);
	philo->last_meal = philo->data->starttime;
	printf("hello from index %d\n", philo->id);
	printf("its starttime %ld\n", philo->data->starttime);
	printf("its last meal %ld\n", philo->last_meal);
	if (philo->data->n_philo == 1)
		return (one_philo_routine(philo));
	return (NULL);
}


/* we can pass only 1 par to the thread so we need to have struct in a struct*/
int	la_grande_bouffe_start(t_data *data, t_philo *philo)
{
	int i;

	data->starttime = time_in_ms();
	// printf("bouffe starttime %ld\n", data->starttime);
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&philo->tid, NULL, (void *)philo_routine, &philo[i]))
			return (msg("Error: pthread_create failure"), 0);
	}
	usleep(100); // makes them to print in order
	return (1);
}

int	la_grande_bouffe_stop(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_join(philo[i].tid, NULL);
		// if (pthread_join(philo[i].tid, NULL) != 0) // GIVES ERROR CUS DEADLOCK
		// 		return (msg("Error: pthread_join"), 0);
	}
	return (1);
}


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
	if (!la_grande_bouffe_start(data, philo))
		return (1); // add protected free
	if (!la_grande_bouffe_stop(data, philo))
		return (1);  // add protected free
	if (!destroy_mutex(data, philo))
		return (1);
	//free data
	return(0);
}