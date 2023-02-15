

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
	while (!sim_stop(philo, 0) && (ms > (time_in_ms() - beginning)))
		usleep(100);
		//usleep(50);
}

// int	check_sim_stop(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->sim_stop_lock);
// 	if (philo->data->sim_stop)
// 	{
// 		pthread_mutex_unlock(&philo->data->sim_stop_lock);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->data->sim_stop_lock);
// 	return (0);
// }

// int	set_sim_stop(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->sim_stop_lock);
// 	{
// 		philo->data->sim_stop = 1;
// 		pthread_mutex_unlock(&philo->data->sim_stop_lock);
// 		return (1);
// 	}
// }

// int i=0 - checking funktion
// int i=1 - changing value
int	sim_stop(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->sim_stop_lock);
	if (i)
	{
		philo->data->sim_stop = 1;
		pthread_mutex_unlock(&philo->data->sim_stop_lock);
		return (1);
	}
	if (philo->data->sim_stop)
	{
		pthread_mutex_unlock(&philo->data->sim_stop_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->sim_stop_lock);
	return (0);
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	// philo->last_meal = philo->data->starttime;
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
		// usleep(5000);
	while (1)
	{
		if (sim_stop(philo, 0))
		// if (check_sim_stop(philo))
			return (NULL);
		philo_eating(philo); // it may finish but print is protected!
		// philo_sleeping(philo);
		print_status(philo, "is sleeping");
		smart_sleep(philo, philo->data->time_to_sleep);
		// philo_thinking(philo);
		print_status(philo, "is thinking");
	}	
	return(NULL);
}

int	single_thread_must_stop(t_philo *philo)
{	
	pthread_mutex_lock(&philo->data->do_lock); //if philo was starving it dies
	if ((time_in_ms() - philo->last_meal) >= philo->data->time_to_die)
	{
		print_status(philo, "died");
		sim_stop(philo, 1);
		pthread_mutex_unlock(&philo->data->do_lock);
		return (1); //return 1 if killed one philo
	} //if he is still alive we check and there was one more arg  - data->fed+1 if he ate right amount of meals
	else if ((philo->data->n_must_eat > 0) && (philo->ate >= philo->data->n_must_eat))
	{ //do_lock is still active here!!!!
		philo->data->fed++; //if they all are fed we exp
		if (philo->data->fed >= philo->data->n_philo)
		{
			sim_stop(philo, 1);
			print_status(philo, "REACHED AMOUNT OF MEALS");
			pthread_mutex_unlock(&philo->data->do_lock);
			return (1);
		}
	} // if he s still alive and there is no limit of meals/they are not reached
	pthread_mutex_unlock(&philo->data->do_lock);
	return (0);
}

void multiple_thread_monitoring(t_data *data)
{
	int i;

	while (1)
	{ //limit is amount of meals
		i = -1;
		data->fed = 0; //used calloc
		while(++i < data->n_philo)
		{
			if (single_thread_must_stop(&data->philo[i]))
				return ;
		} 
		usleep(10);
	}
	// int loop;
	// int i;

	// loop = 1;
	// while (loop)
	// { //limit is amount of meals
	// 	i = -1;
	// 	// data->fed = 0; //used calloc
	// 	while(++i < data->n_philo)
	// 	{
	// 		if (loop && single_thread_must_stop(&data->philo[i]))
	// 			loop = 0;
	// 	}
	// 	usleep(10);
	// }
}

int	simulation_start(t_data *data)
{
	int	i;

	if (data->n_philo == 1)
		return (simulation_for_one(data));
	// data->starttime = time_in_ms();
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

	data = malloc(1 * sizeof(t_data));
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