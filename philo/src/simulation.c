/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:50:24 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/03/15 15:47:29 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
assignment says:
every philo (even single one) should be the thread,
every philo has one fork which is protected by mutex

we have to build this function in the same way as others

philo will be not interrupted by death of the others,
so no smart_sleep needed
*/
void	*lone_philo_routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	pthread_mutex_lock(&philo->data->forks[0]);
	print_fork(philo);
	usleep(philo->data->time_to_die * 1000);
	print_die(philo);
	pthread_mutex_unlock(&philo->data->forks[0]);
	return (NULL);
}

/* 
to protect from a deadlock, let the half of philos to wait.
chosen delay time -  time other philo needs to finish their meals.
previous delay time was usleep(2500); but it didnt work with
input 100 500 200 200

infinite loop (may me interupted when someone died or ate enough)

during eating and sleeping we use smart_sleep function,
it interrupts sleeping if someone died,
so program doesnt hang until wake up and finishes it execution right after.

could have added here on the start: philo->last_meal = philo->data->starttime;
bud did earlier to avod data_races
*/
void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->data->n_philo == 1)
		return (lone_philo_routine(philo));
	if (philo->id % 2)
		usleep(philo->data->time_to_eat * 1000);
	while (1)
	{
		if (check_sim_stop(philo))
			return (NULL);
		philo_eating(philo);
		if (check_sim_stop(philo))
			return (NULL);
		philo_sleeping(philo);
		if (check_sim_stop(philo))
			return (NULL);
		philo_thinking(philo);
	}	
	return (NULL);
}

/* 
each philo is a thread, 
we initialized them duting init_data

at the same time we run multiple_thread_monitoring(data);
i don't know if i should create thread for it

could have added on the beginning data->starttime = time_in_ms()
but it was moved to data_init to avoid data_races

SIC! do we need to add usleep in while loop? 
in my case it's working but it may crash on slower computer.
*/
int	simulation_start(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->philo[i].philo_tid, NULL,
				&routine, &data->philo[i]))
			return (msg("pthread_create error"), 0);
	}
	multiple_thread_monitoring(data);
	return (1);
}

/*
notice that when routine function/simulation is not perfect
we should silent pthread_join check,
because it will give us error from deadlock
*/
int	simulation_stop(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_join(data->philo[i].philo_tid, NULL))
			return (msg("pthread_join error"), 0);
	}
	if (!destroy_mutex(data))
		return (msg("destroy_mutex error"), 0);
	return (1);
}
