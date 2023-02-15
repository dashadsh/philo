
#include "../inc/philo.h"

int	init_mutex(t_data *data) // mutexes - all forks, global mutexes
{
	int	i;

	data->forks = malloc(data->n_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (msg("malloc error"), 0);
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (msg("pthread_mutex_init error"), 0);
	}
	if (pthread_mutex_init(&(data->sim_stop_lock), NULL))
			return (msg("pthread_mutex_init error"), 0);
	// // ADD GLOBAL MUTEXES:
	if (pthread_mutex_init(&(data->write_lock), NULL))
			return (msg("pthread_mutex_init error"), 0);
	// if (pthread_mutex_init(&(data->dead_flag_lock), NULL))
	// 		return (msg("pthread_mutex_init error"), 0);
	// if (pthread_mutex_init(&(data->all_ate_lock), NULL))
	// 		return (msg("pthread_mutex_init error"), 0);
	// if (pthread_mutex_init(&(data->ate_lock), NULL))
	// 		return (msg("pthread_mutex_init error"), 0);
	if (pthread_mutex_init(&(data->do_lock), NULL))
			return (msg("pthread_mutex_init error"), 0);
	return (1);
}

int	destroy_mutex(t_data *data) // mutexes - all forks, global mutexes
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_destroy(&(data->forks[i])))
			return (msg("pthread_mutex_destroy error"), 0);
	}
	// ADD GLOBAL MUTEXES:
	// if (pthread_mutex_destroy(&(data->write_lock)))
	// 		return (msg("pthread_mutex_destroy error"), 0);
	// if (pthread_mutex_destroy(&(data->dead_flag_lock)))
	// 		return (msg("pthread_mutex_destroy error"), 0);
	// if (pthread_mutex_destroy(&(data->all_ate_flag_lock)))
	// 		return (msg("pthread_mutex_destroy error"), 0);
	// if (pthread_mutex_destroy(&(data->ate_lock)))
	// 		return (msg("pthread_mutex_destroy error"), 0);
	// if (pthread_mutex_destroy(&(data->do_lock)))
	// 		return (msg("pthread_mutex_destroy error"), 0);
	return (1);
}
