
#include "../inc/philo.h"

void	free_all(t_data *data)
{
	// int	i;

	if (!data)
		return ;
	if (data->forks)
		free(data->forks);
	if (data->philo)
	{
		// i = -1;
		// while (++i < data->n_philo)
		// {
		// 	if (data->philo[i])
		// 		free(data->philo);
		// }
		free(data->philo);
	}
		free(data);
}

// void	free_all(t_data *data)
// {
// 	if (data->forks)
// 		free(data->forks);
// 	if (data->philo)
// 		free(data->philo);
// 	if (data)
// 		free(data);
// }
