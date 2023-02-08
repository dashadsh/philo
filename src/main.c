

#include "../inc/philo.h"
/*
External funct.:

memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/

void	err(char *s)
{
	printf("%s", s);
}

// int	err(char *s)
// {
// 	printf("%s\n", s);
// 	// return (1);
// }

int	digits_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

// int	four_five_args(int ac)
// {
// 	if (ac < 5 || ac > 6)
// 		return (0);
// 	return (1);
// }

// 1. add check for MAX_PHILOS
//	if (i == 1 && nb > MAX_PHILOS))
//
// 2. check for time needed??

int	valid_input(int ac, char **av)
{
	int	i;
	int	nb;

	i = 0;
	while (++i < ac)
	{
		if (!digits_only(av[i]))
			return (0);
		nb = philo_atoi(av[i]);
		if (nb <= 0)
			return (0);
	}
	if (philo_atoi(av[1]) > PHILO_MAX) // do we need this check??
		return (0);
	return (1);
}

	// if (philo_atoi(av[2]) < philo_atoi(av[3]) + philo_atoi(av[4]))
	// {
	// 	return (error(ERR_TIME), 0);
	// }

// one philosopher routine

// (one_philosopher(table))

// init_philosophers(table);

// init_mutex(table);

void	init_data(t_data *data, int ac, char **av)
{
	data->n_philo = philo_atoi(av[1]);
	data->time_to_die = philo_atoi(av[2]);
	data->time_to_eat = philo_atoi(av[3]);
	data->time_to_sleep = philo_atoi(av[4]);
	data->n_to_eat = -1;
	if (ac == 6)
		data->n_to_eat = philo_atoi(av[5]);
	// data->dead = 0; //
	// data->all_ate = 0; ///???
	// if data->n_philo == 1  ONE PHILO

	// init_philosophers(table);
	// init_mutex(table);
}

int	init_mutex(t_data *data)
{
	data->forks_mutex = ft_calloc((data->n_philo), sizeof(pthread_mutex_t)); // malloc is *, calloc is ,
	if (!data->forks_mutex)
		return (0);
	int i;
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks_mutex[i], NULL))
			return (0); // return smth in case of error
		//init mutex for every philo? sleep
	}
	if (pthread_mutex_init->)
	//meal check
	__dead2
	return (1);
}


int	init_all(t_data *data, int ac, char **av)
{
	init_data(data, ac, av);
	if (!init_mutex(data))
		return (0);
	return (1);
}



int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (err(ARG_AMT), 1);
	if (!valid_input(ac, av))
		return (err(INPUT), 1);

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (err(ALLOC), 1);
	if (!init_all(data, ac, av))
		return (1);
	
	return (0);
}


	 //no * -> . 
	//echo $?