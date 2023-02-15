


#include "../inc/philo.h"

/*
External funct.:

memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/

// void	*lone_philo_routine(void *void_data)
// {
// 	t_data *data;

// 	data = (t_data *)void_data;
// 	// printf("hello from index %d\n", philo->id);
// 	// printf("amt of philo %d\n", philo->data->n_philo);
// 	printf("0 philo 1 has taken a fork\n");
// 	printf("%d philo 1 died\n", data->time_to_die);
// 	return (NULL);
// }

// int	simulation_for_one(t_data *data)
// {
// 	if (pthread_create(&data->philo[0].philo_tid, NULL, &lone_philo_routine, data))
// 		return (msg("pthread_create error"), 0);
// 	return (1);
// }

void	*lone_philo_routine2(void *void_philo)
{
	t_philo *philo;

	philo = (t_philo *)void_philo;
	pthread_mutex_lock(&philo->data->forks[0]);
	print_status(philo, "has taken the fork");
	smart_sleep(philo, philo->data->time_to_die);
	print_status(philo, "died");
	pthread_mutex_unlock(&philo->data->forks[0]);
	return (NULL);
}