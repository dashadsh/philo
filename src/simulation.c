


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


void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	// philo->last_meal = philo->data->starttime; //did earlier to avod data_races

	if (philo->data->n_philo == 1)
		return(lone_philo_routine2(philo));

	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
		// usleep(5000);
	while (1)
	{
		// if (sim_stop(philo, 0))
		if (check_sim_stop(philo))
			return (NULL);
		philo_eating(philo); // it may finish but print is protected!
		philo_sleeping(philo);
		philo_thinking(philo);
	}	
	return(NULL);
}

int	simulation_start(t_data *data)
{
	int	i;

	// if (data->n_philo == 1) // moved it to routine
	// 	return (simulation_for_one(data));
	// data->starttime = time_in_ms(); //did it earlier to avoid data_races
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->philo[i].philo_tid, NULL, &routine, &data->philo[i]))
			return (msg("pthread_create error"), 0);
		// usleep(200);
	}
	multiple_thread_monitoring(data);
	return (1);
}

int	simulation_stop(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		// pthread_join(data->philo[i].philo_tid, NULL); // GIVES ERROR CUS DEADLOCK when start coding
		if (pthread_join(data->philo[i].philo_tid, NULL))
				return (msg("pthread_join error"), 0);
	}
	if (!destroy_mutex(data))
		return (msg("destroy_mutex error"), 0);
	return (1);
}
