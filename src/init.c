

#include "../inc/philo.h"

/*
External funct.:

memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/
void extract_args(t_data *data, int ac, char **av)
{
	data->n_philo = philo_atoi(av[1]);
	data->time_to_die = philo_atoi(av[2]);
	data->time_to_eat = philo_atoi(av[3]);
	data->time_to_sleep = philo_atoi(av[4]);
	data->n_must_eat = -1;
	if (ac == 6)
		data->n_must_eat = philo_atoi(av[5]);
}


t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return(msg("Alloc error"), NULL);
	extract_args(data, ac, av);
	if (!init_mutex(data)) // mutexes first, so philos can share them
		return (msg("Mutex init error"), NULL);
	return(data);
}

// assigning forks id's 
// should i change approach which fork to assign??
//
// .times_ate -  to count until all reach n_must_eat
// where we add a flag all_ate? ALL need to eat this amt of times
//
// init LAST_MEAL = start time/ time of last meal start
// last_meal - we add it in start of  routine
// 
t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;
	int	i;

	philo = ft_calloc(data->n_philo, sizeof(t_philo));
	if (!philo)
		return (msg("Philo struct alloc error"), NULL);
	i = -1;
	while (++i < data->n_philo)
	{
		philo[i].data = data;
		// printf("%d\n", philo[i].data.time_to_die);
		philo[i].id = i;
		// philo[i].times_ate = 0; // calloc used
		philo[i].l_fork_index = i;
		philo[i].r_fork_index = (i + 1) % data->n_philo;
		philo[i].l_fork_ptr = &data->forks[i]; // why &
		philo[i].r_fork_ptr = &data->forks[(i + 1) % data->n_philo];
		// printf("%p %p\n", &data->forks[i], philo[i].l_fork_ptr);
		//
		// if (i % 2)
		// {
		// 	data->philo[i].l_fork_index = (i + 1) % data->n_philo;
		// 	data->philo[i].r_fork_index = i;
		// // }
		//
		// printf ("philo id %d, lfork %d, rfork %d\n", philo[i].id, philo[i].l_fork_index, philo[i].r_fork_index);
		// printf ("die %d eat %d sleep %d \n", philo[i].data.time_to_die, philo[i].data.time_to_eat, philo[i].data.time_to_sleep);
	}
	return(philo);
}