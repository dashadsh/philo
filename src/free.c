
#include "../inc/philo.h"

// protect from double free?
// separate function to destroy mutexes????
	// while (++i < data->n_philo)
	// 	pthread_mutex_destroy(data->forks + i); //correct?????
	// //destroy global mutexes


void	free_all(t_data *data, t_philo *philo)
{
	if (data != NULL)
		free(data);  // ADD A FUNC TO FREE DATA PROPERLY
	if (philo != NULL)
		free(philo);
}