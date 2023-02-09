
#include "../inc/philo.h"


void	free_all(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_destroy(data->forks + i); //correct?????
	//destroy global mutexes 
	free(data->forks);
	free(data);
	free(philo);
}