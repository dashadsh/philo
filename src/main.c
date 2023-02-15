

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


void	print_status(t_data *data, int id, char *s)
{
	pthread_mutex_lock(&(data->write_lock));
	if (!(data->dead_flag)) //  !data->all_ate_flag)
	{
		printf("%ld ", time_in_ms() - data->starttime);
		printf("%i ", id + 1);
		printf("%s\n", s);
	}
	pthread_mutex_unlock(&(data->write_lock));
	return ;
}

// void	mysleep(t_data *data, long time_to_sleep)
// {
// how to monitor death during the sleep??
// }

void	philo_eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->l_fork]));
	print_status(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->forks[philo->r_fork]));
	print_status(data, philo->id, "has taken a fork");
	print_status(data, philo->id, "is eating");
	philo->last_meal = time_in_ms();
	usleep(data->time_to_eat);
	// mysleep(data, data->time_to_eat);
	philo->ate++; // CHANGING LOCAL STUFF
	pthread_mutex_unlock(&(data->forks[philo->l_fork]));
	pthread_mutex_unlock(&(data->forks[philo->r_fork]));
}

void	philo_sleping(t_philo *philo)
{
		print_status(philo->data, philo->id, "is sleeping");
		usleep(philo->data->time_to_sleep);
		// mysleep(philo->data, philo->data->time_to_sleep);
}

void	*routine2(t_philo *philo)
{
	while (1)
	{
		philo_eating(philo);
		//ALL ATE FLAG LOCK CHECK??
		philo_sleping(philo);
		print_status(philo->data, philo->id, "is thinking");
		//DEAD FLAG LOCK CHECK??
	}
	return (NULL);
}



void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	philo->last_meal = philo->data->starttime;
	if (philo->id % 2)
	{
		usleep(2500);
	}
	return(routine2(philo));
}


int	simulation_start(t_data *data)
{
	int i;

	if (data->n_philo == 1)
		return (simulation_for_one(data));
	data->starttime = time_in_ms();
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->philo[i].philo_tid, NULL, &routine, &data->philo[i]))
			return (msg("pthread_create error"), 0);
		// usleep(100);
	}
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