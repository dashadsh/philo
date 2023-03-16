/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:13:19 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/03/15 23:51:20 by dgoremyk         ###   ########.fr       */
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

for even amount of philos: 
the logic behind this problem says us, 
that if we have no time lag, since only half of the philos can eat in a time, 
if the general time is eat_time*2, it should be enough time for all to eat. 

but bcz of mutexes we have time lag (mutexes!), the closest die_time to the 
eattime*2 the better the program.

for odd, since we have half philos and half philos and 1 extra philo that 
can eat at a time, if we have timetoeat*3 as the die time, it should be enough
for everyone.

since there is time lag, the closer the time, that odd number of philos can eat 
forever to the eat timeX3 the better the algorithem

for example:
./philo 151 610 200 200
if it runs forever and no one dies its a perfect and fast program
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
