/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:13:12 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/02/17 21:22:12 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
malloc is preferred since ft_calloc is not optimised
when malloc used all data must be initialized to prevent conditional jumps

i save starttime here instead of simulation_start_function
because there it created timing problems

probably they could be fixed dy adding a function which synchronizes 
start of all threads

then i would need to add here: data->starttinme = 0;
*/
void	extract_args(t_data *data, int ac, char **av)
{
	data->n_philo = philo_atoi(av[1]);
	data->time_to_die = philo_atoi(av[2]);
	data->time_to_eat = philo_atoi(av[3]);
	data->time_to_sleep = philo_atoi(av[4]);
	data->n_must_eat = -1;
	if (ac == 6)
		data->n_must_eat = philo_atoi(av[5]);
	data->starttime = time_in_ms();
	data->fed = 0;
	data->sim_stop = 0;
}

/*
inside t_data i malloc space for all philosophers

i save lastmeal_time (=starttime) here instead of 
*routine function because there it created timing problems.

probably they could be fixed dy adding a function which synchronizes 
start of all threads.
then i would need to add: data->philo[i].last_meal = 0;

every philo gets alias of t_data, 
because we will pass only ONE argument to each thread,
so it will be data of a single philosopher. But this philosopher will still 
have access to global data

every philo gets index of left and right fork assigned

there is an approach to switch order philos are taking forks,
but i didn't notice any difference:
if (i % 2)
{
data->philo[i].l_fork = (i + 1) % data->n_philo;
data->philo[i].r_fork = i;
}
*/
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
		data->philo[i].last_meal = data->starttime;
		data->philo[i].data = data;
	}
	return (1);
}

/*
when initialized philos
every philo gets index of left and right fork assigned

it's probably possible to assign pointers to mutexes
then order - init_mutex->init_philo will be crucial
*/
int	init_data(t_data *data, int ac, char **av)
{
	extract_args(data, ac, av);
	if (!init_mutex(data))
		return (msg("init_mutex error"), 0);
	if (!init_philo(data))
		return (msg("init_philo error"), 0);
	return (1);
}
