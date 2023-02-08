

#include "../inc/philo.h"

/*
External funct.:

memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/

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

t_philo *init_philos(t_data *data)
{
	t_philo *philos;

	philos = ft_calloc(data->n_philo, sizeof(t_philo));
	if (!philos)
		return (NULL);

	int i;
	
	i = -1;
	while (++i < data->n_philo)
	{
		philos[i].data = *data;
		// printf("%d\n", philos[i].data.time_to_die);
		philos[i].id = i;
		// printf("%d\n", philos[i].id);
		philos[i].times_ate = 0;
	}
	return(philos);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return(msg("Alloc error"), NULL);
	extract_args(data, ac, av);
	data->philos = init_philos(data);
	if (!data->philos)
		return(0);
	return(data);
}

int	main(int ac, char **av)
{
	t_data *data;

	if (!valid_input(ac, av))
		return (msg("Input is invalid"), 1);

	data = init_data(ac, av);
	if (!data)
		return(1);
	return(0);
}