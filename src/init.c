
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
}

int	init_philo(t_data *data)
{
	int	i;

	data->philo = ft_calloc(data->n_philo, sizeof(t_philo));
	if (!data->philo)
		return (msg("ft_calloc (data->philo) error"), 0);
	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].id = i;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->n_philo;
		data->philo[i].data = data;
		// printf ("philo id %d, lfork %d, rfork %d\n", data->philo[i].id, data->philo[i].l_fork, data->philo[i].r_fork);
		// printf ("ttd %d\n\n", data->philo[i].data->time_to_die);
		// if (i % 2)
		// {
		// 	data->philos[i].l_fork = (i + 1) % data->n_philo;
		// 	data->philos[i].r_fork = i;
		// }
	}
	return(1);
}

int	init_data(t_data *data, int ac, char **av)
{
	extract_args(data, ac, av);
	// printf()
	if (!init_mutex(data)) // mutexes first, so philos can share them
		return (msg("init_mutex error"), 0);
	if (!init_philo(data))
		return (msg("init_philo error"), 0);
	return(1);
}