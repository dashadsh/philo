/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:09:21 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/02/16 14:13:07 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* actions for one single thread*/

/* 
checks if someone died during waiting time

if it happened - stop waiting, so program has chance to finish right after
death occured
*/
void	smart_sleep(t_philo *philo, long ms)
{
	long	beginning;

	beginning = time_in_ms();
	while (!check_sim_stop(philo) && (ms > (time_in_ms() - beginning)))
		usleep(50);
}

/*
used do_lock in the middle to access safely
time_in_ms() and save it locally in info of THIS philo
not sure if placing for saving current time is correct
*/
void	philo_eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->l_fork]));
	print_fork(philo);
	// print_status(philo, "has taken a fork");
	pthread_mutex_lock(&(data->forks[philo->r_fork]));
	print_fork(philo);
	// print_status(philo, "has taken a fork");
	print_eat(philo);
	// print_status(philo, "is eating");
	smart_sleep(philo, data->time_to_eat);
	// usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&(data->do_lock));
	philo->last_meal = time_in_ms();
	philo->ate++;
	pthread_mutex_unlock(&(data->do_lock));
	pthread_mutex_unlock(&(data->forks[philo->l_fork]));
	pthread_mutex_unlock(&(data->forks[philo->r_fork]));
}

void	philo_sleeping(t_philo *philo)
{
	print_sleep(philo);
	// print_status(philo, "is sleeping");
	smart_sleep(philo, philo->data->time_to_sleep);
	// usleep(philo->data->time_to_sleep * 1000);
}

void	philo_thinking(t_philo *philo)
{
	print_think(philo);
	// print_status(philo, "is thinking");
}
