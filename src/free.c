
#include "../inc/philo.h"

void	free_all(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	if (data)
		free(data);
}
