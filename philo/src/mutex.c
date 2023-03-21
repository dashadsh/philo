/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:50:19 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/02/16 13:54:51 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
every fork is a mutex
number of philos = number of forks

inside of t_data we mallo space for all mutexes

there are 3 global mutexes shared within all philos:
1. sim_stop_lock - used to check and change the flag when simulation 
should stop
2. write_lock - to protect stdout from accessing it at the same time 
(output will be corrupted otherwise)
3. do_lock - used to sync with current time_in_ms() and save it in 
last_meal variable
*/
int	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(data->n_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (msg("malloc error (data->forks)"), 0);
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (msg("pthread_mutex_init error"), 0);
	}
	if (pthread_mutex_init(&(data->sim_stop_lock), NULL))
		return (msg("pthread_mutex_init error"), 0);
	if (pthread_mutex_init(&(data->write_lock), NULL))
		return (msg("pthread_mutex_init error"), 0);
	if (pthread_mutex_init(&(data->do_lock), NULL))
		return (msg("pthread_mutex_init error"), 0);
	return (1);
}

int	destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_destroy(&(data->forks[i])))
			return (msg("pthread_mutex_destroy error"), 0);
	}
	if (pthread_mutex_destroy(&(data->write_lock)))
		return (msg("pthread_mutex_destroy error"), 0);
	if (pthread_mutex_destroy(&(data->sim_stop_lock)))
		return (msg("pthread_mutex_destroy error"), 0);
	if (pthread_mutex_destroy(&(data->do_lock)))
		return (msg("pthread_mutex_destroy error"), 0);
	return (1);
}
