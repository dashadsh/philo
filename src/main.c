

#include "../inc/philo.h"

/*
External funct.:

memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/


int	init_mutex(t_data *data) // mutexes for all forks, global mutexes
{
	int	i;

	data->forks = malloc(data->n_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (0);
	}
	// ADD GLOBAL MUTEXES: printing, dead philo, min amt to eat??
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = ft_calloc(data->n_philo, sizeof(t_philo));
	if (!data->philos)
		return (0);
	i = -1;
	while (++i < data->n_philo)
	{
		data->philos[i].data = *data;
		// printf("%d\n", philos[i].data.time_to_die);
		data->philos[i].id = i;
		// printf("%d\n", philos[i].id);
		data->philos[i].times_ate = 0;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = (i + 1) % data->n_philo;
		if (i % 2)
		{
			data->philos[i].l_fork = (i + 1) % data->n_philo;
			data->philos[i].r_fork = i;
		}
		printf ("philo id %d, lfork %d, rfork %d\n", data->philos[i].id, data->philos[i].l_fork, data->philos[i].r_fork);
	}
	return(1);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return(msg("Alloc error"), NULL);
	extract_args(data, ac, av);
	extract_starttime(data);
	if (!init_mutex(data)) // mutexes first, so philos can share them
		return(0);
	if (!init_philos(data))
		return (0);
	return(data);
}

int	main(int ac, char **av)
{
	t_data *data;

	if (!valid_input(ac, av))
		return (msg("Input is invalid"), 1);

	data = init_data(ac, av);
	if (!data)
		return(msg("Initialisation error"), 1);
	//free data
	return(0);
}