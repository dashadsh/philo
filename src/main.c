

#include "../inc/philo.h"

/*
External funct.:

memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/

/* checks if someone died during sleep*/


void	smart_sleep(t_philo *philo, long ms)
{
	long	beginning;

	beginning = time_in_ms();
	while (!check_sim_stop(philo) && (time_in_ms() - beginning) < ms)
		usleep(50);
}

int	check_sim_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->sim_stop_lock);
	if (philo->data->sim_stop)
	{
		pthread_mutex_unlock(&philo->data->sim_stop_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->sim_stop_lock);
	return (0);
}


// int	single_killer(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->do_lock);
// 	if ((time_in_ms() - philo->last_meal) >= philo->data->time_to_die)
// 	{
// 		print_status(philo, "died");
// 		set_sim_stop(philo);
// 		pthread_mutex_unlock(&philo->data->do_lock);
// 		return (1);
// 	}
// 	else if (philo->)
// }

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	philo->last_meal = philo->data->starttime;
	if (philo->id % 2)
		usleep(5000);
	while (1)
	{
		if (check_sim_stop(philo))
			return (NULL);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}	
	return(NULL);
}

int	set_sim_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->sim_stop_lock);
	{
		philo->data->sim_stop = 1;
		pthread_mutex_unlock(&philo->data->sim_stop_lock);
		return (1);
	}
}

// 	void killer(t_philo *philo)
// {	
// 	pthread_mutex_lock(&philo->data->do_lock);
// 	if ((time_in_ms() - philo->last_meal) >= philo->data->time_to_die)
// 	{
// 		print_status(philo, "died");
// 		set_sim_stop(philo);
// 		pthread_mutex_unlock(&philo->data->do_lock);
// 		return (1); //return 1 if killed one philo
// 	}
// 	else if ((philo->data->n_must_eat != -1) && philo->ate >= philo->data->)
// }

// void multiple_killer(t_data *data)
// {
// }

int	simulation_start(t_data *data)
{
	int	i;

	if (data->n_philo == 1)
		return (simulation_for_one(data));
	data->starttime = time_in_ms();
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->philo[i].philo_tid, NULL, &routine, &data->philo[i]))
			return (msg("pthread_create error"), 0);
		// usleep(200);
	}
	// multiple_killer(data);
	return (1);
}

int	simulation_stop(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_join(data->philo[i].philo_tid, NULL);
		// if (pthread_join(philo[i].tid, NULL)) // GIVES ERROR CUS DEADLOCK
		// 		return (msg("pthread_join error"), 0);
	}
	if (!destroy_mutex(data))
		return (msg("destroy_mutex error"), 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!valid_input(ac, av))
		return (msg("input invalid"), 1);

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return(msg("ft_calloc (t_data *data) error"), 1);
	if (!init_data(data, ac, av))
		return(msg("init_data error"), 1); // free
	if (!simulation_start(data))
		return(msg("simulation_start error"), 1);
	if (!simulation_stop(data))
		return (msg("simulation_stop error"), 1);
	free_all(data);
	return(0);
}