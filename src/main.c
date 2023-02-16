/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:13:19 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/02/16 14:13:25 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
External funct.:

memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/

/* 
used to print error message in RED colour
*/
void	msg(char *s)
{
	printf("\033[1;31m");
	printf("%s\n", s);
}

/*
free_all is a protected function which is freeing only if
there's something to free
*/
void	free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!valid_input(ac, av))
		return (msg("input invalid"), 1);

	data = malloc(1 * sizeof(t_data));
	if (!data)
		return (msg("malloc error (t_data *data)"), 1);
	if (!init_data(data, ac, av))
		return (msg("init_data error"), free_all(data), 1);
	if (!simulation_start(data))
		return (msg("simulation_start error"), free_all(data), 1);
	if (!simulation_stop(data))
		return (msg("simulation_stop error"), free_all(data), 1);
	free_all(data);
	return (0);
}