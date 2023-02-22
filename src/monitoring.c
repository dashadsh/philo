/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:07:05 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/02/22 20:36:42 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* 
function which checks if 
flag philo->data->sim_stop == 1

used to stop the action which is running at the moment

check it many times during waiting time
to prevent philo from still sleeping/eating if someone died inbetween
*/
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

/*
function which sets the flag to 1

if any other function "sees" it, it's execution should stop
*/
int	set_sim_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->sim_stop_lock);
	{
		philo->data->sim_stop = 1;
		pthread_mutex_unlock(&philo->data->sim_stop_lock);
		return (1);
	}
}

/*
function is monitoring one single thread one time

first it checks if philo was starving -> then he: 
will die
print message
set the simulation_stop_flag to 1
return 1 

if he s not dead and we have 6 args (lock is still active!)
(need to feed philos N amout of times)
if this current philo ate alreasy those times, we add +1
to fed variable in data and check if ded == n_philo.
if we fed all philos:
set the simulation_stop_flag to 1
return 1

if he s still alive and there is no limit of meals/they are not reached
return 0
*/
int	single_thread_must_stop(t_philo *philo)
{	
	pthread_mutex_lock(&philo->data->do_lock);
	if ((time_in_ms() - philo->last_meal) >= philo->data->time_to_die)
	{
		print_die(philo);
		set_sim_stop(philo);
		pthread_mutex_unlock(&philo->data->do_lock);
		return (1);
	}
	else if ((philo->data->n_must_eat > 0)
		&& (philo->ate >= philo->data->n_must_eat))
	{
		philo->data->fed++;
		if (philo->data->fed >= philo->data->n_philo)
		{
			set_sim_stop(philo);
			pthread_mutex_unlock(&philo->data->do_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->data->do_lock);
	return (0);
}

/*
data->fed reset it to zero, 
because we check from zero to full in "single thread must stop"

could be solved using static variable

not sure if i'm correct with usleep time
*/
void	multiple_thread_monitoring(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		data->fed = 0;
		while (++i < data->n_philo)
		{
			if (single_thread_must_stop(&data->philo[i]))
				return ;
		}
		usleep(200);
	}
}
