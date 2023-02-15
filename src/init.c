
#include "../inc/philo.h"

void	extract_args(t_data *data, int ac, char **av)
{
	data->n_philo = philo_atoi(av[1]);
	data->time_to_die = philo_atoi(av[2]);
	data->time_to_eat = philo_atoi(av[3]);
	data->time_to_sleep = philo_atoi(av[4]);
	data->n_must_eat = -1;
	if (ac == 6)
		data->n_must_eat = philo_atoi(av[5]);
	data->starttime = time_in_ms(); // do it here to avoid data_race
	data->fed = 0;
	data->sim_stop = 0;
}

int	init_philo(t_data *data)
{
	int	i;

	data->philo = malloc(data->n_philo * sizeof(t_philo));
	if (!data->philo)
		return (msg("ft_calloc (data->philo) error"), 0);
	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].ate = 0;
		data->philo[i].id = i;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->n_philo;
		data->philo[i].last_meal = data->starttime; // // do it here to avoid data_race
		// data->philo[i].last_meal = 0;
		data->philo[i].data = data;
		// if (i % 2)
		// {
		// 	data->philo[i].l_fork = (i + 1) % data->n_philo;
		// 	data->philo[i].r_fork = i;
		// }
	}
	return(1);
}

int	init_data(t_data *data, int ac, char **av)
{
	extract_args(data, ac, av);
	if (!init_mutex(data)) // mutexes first, so philos can share them
		return (msg("init_mutex error"), 0);
	if (!init_philo(data))
		return (msg("init_philo error"), 0);
	return(1);
}