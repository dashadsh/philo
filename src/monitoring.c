
#include "../inc/philo.h"

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

int	set_sim_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->sim_stop_lock);
	{
		philo->data->sim_stop = 1;
		pthread_mutex_unlock(&philo->data->sim_stop_lock);
		return (1);
	}
}

// int i=0 - checking funktion
// int i=1 - changing value
// int	sim_stop(t_philo *philo, int i)
// {
// 	pthread_mutex_lock(&philo->data->sim_stop_lock);
// 	if (i)
// 	{
// 		philo->data->sim_stop = 1;
// 		pthread_mutex_unlock(&philo->data->sim_stop_lock);
// 		return (1);
// 	}
// 	if (philo->data->sim_stop)
// 	{
// 		pthread_mutex_unlock(&philo->data->sim_stop_lock);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->data->sim_stop_lock);
// 	return (0);
// }

int	single_thread_must_stop(t_philo *philo)
{	
	pthread_mutex_lock(&philo->data->do_lock); //if philo was starving it dies
	if ((time_in_ms() - philo->last_meal) >= philo->data->time_to_die)
	{
		print_status(philo, "died");
		set_sim_stop(philo);
		// sim_stop(philo, 1);
		pthread_mutex_unlock(&philo->data->do_lock);
		return (1); //return 1 if killed one philo
	} //if he is still alive we check and there was one more arg  - data->fed+1 if he ate right amount of meals
	else if ((philo->data->n_must_eat > 0) && (philo->ate >= philo->data->n_must_eat))
	{ //do_lock is still active here!!!!
		philo->data->fed++; //if they all are fed we exp
		if (philo->data->fed >= philo->data->n_philo)
		{
			set_sim_stop(philo);
			// sim_stop(philo, 1);
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
		// data->fed = 0; //used calloc
		while(++i < data->n_philo)
		{
			if (single_thread_must_stop(&data->philo[i]))
				return ;
		} 
		usleep(10);
	}
}