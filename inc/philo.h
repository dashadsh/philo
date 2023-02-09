/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:24:31 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/02/09 12:52:28 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h> 
# include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define PHILO_MAX 250

// timestamp_in_ms X has taken a fork 
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died

typedef struct s_philo	t_philo;

//	pthread_mutex_t	*forks;  - variable to save mutexes 
typedef struct s_data
{
	long			starttime;
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_must_eat;

	pthread_mutex_t	*forks;
}	t_data;
// SIM_STOP_FLAG - extract args // DEAD PHILO
// how to count ALL_ATE?

// 	int	l_fork; // id of fork which philo will take first
//	int	r_fork; // used to have an ID of fork mutex
typedef struct s_philo
{
	int		id;
	int		times_ate;
	int		l_fork;
	int		r_fork;
	t_data	data;
}	t_philo;

//-------------

void	extract_starttime(t_data *data);
void	extract_args(t_data *data, int ac, char **av);
t_data	*init_data(int ac, char **av);

//-------------

void	msg(char *s);
int		contains_digits(int ac, char **av);
int		contains_integers(int ac, char **av);
int		valid_input(int ac, char **av);

//-------------

int		philo_atoi(const char *s);
int		are_digits(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

//-------------

long	current_time_in_ms(void);

//-------------

void	free_all(t_data *data, t_philo *philo);

#endif