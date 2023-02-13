
#include "../inc/philo.h"

int	init_mutex(t_data *data) // mutexes - all forks, global mutexes
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
	// ADD GLOBAL MUTEXES:
	// PRINT: what else (dead, min amt to eat?)
	return (1);
}

int	destroy_mutex(t_data *data, t_philo *philo) // mutexes - all forks, global mutexes
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_destroy(&(data->forks[i])))
			return (msg("Error: unable to destroy mutex"), 0);
	}
	// ADD GLOBAL MUTEXES:
	// PRINT: what else (dead, min amt to eat?)
	return (1);
}
