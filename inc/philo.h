/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:24:31 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/02/17 21:23:00 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h> 
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

// timestamp_in_ms X has taken a fork 
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died

typedef struct s_philo	t_philo;

// used long for starttime - not sure if longlong needed?
//
// args of program we save as:
// int				n_philo;
// int				time_to_die;
// int				time_to_eat;
// int				time_to_sleep;
// int				n_must_eat;
//
// fed - used to count if all philos ate enough times
// sim_stop - used as bool flag to check if sumulation must stop/stopped
//
// t_philo			*philo; - every philo is a thread
// pthread_mutex_t	*forks; - array of mutexes
// pthread_mutex_t	write_lock; - lock for stdio so output is not corrupted
// pthread_mutex_t	do_lock; - lock for any local change/time check
// pthread_mutex_t	sim_stop_lock; - lock to set sim_stop flag

typedef struct s_data
{
	long			starttime;

	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_must_eat;

	int				fed;
	int				sim_stop;

	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	do_lock;
	pthread_mutex_t	sim_stop_lock;
}	t_data;

// every philo is a thread
// it s ID is saved as philo_tid
// they all are saved insida of data_struct
//
// int			id; - NR of philo
// int			ate; - will be needed to count amt of meals
// int			l_fork;  - id of fork which philo will take first
// 				used to have an ID of fork mutex
// long		last_meal;  start of the program by default
//				used to check if philo must die
// t_data		*data; - since we can pass one arg to routine
// 				we need to be sure that EVERY philo has access to global data

typedef struct s_philo
{
	pthread_t	philo_tid;
	int			id;
	int			ate;
	int			l_fork;
	int			r_fork;
	long		last_meal;
	t_data		*data;
}	t_philo;

// ARG CHECK
int		contains_digits(int ac, char **av);
int		contains_integers(int ac, char **av);
int		valid_input(int ac, char **av);

//EAT_SLEEP_THINK
void	smart_sleep(t_philo *philo, long ms);
void	philo_eating(t_philo *philo);
void	philo_sleeping(t_philo *philo);
void	philo_thinking(t_philo *philo);

// FREE
void	free_all(t_data *data);

// INIT
void	extract_args(t_data *data, int ac, char **av);
int		init_philo(t_data *data);
int		init_data(t_data *data, int ac, char **av);

// MAIN
void	msg(char *s);
int		main(int ac, char **av);

// MESSAGE
void	print_fork(t_philo *philo);
void	print_eat(t_philo *philo);
void	print_sleep(t_philo *philo);
void	print_think(t_philo *philo);
void	print_die(t_philo *philo);

//MONITORING
int		check_sim_stop(t_philo *philo);
int		set_sim_stop(t_philo *philo);
int		single_thread_must_stop(t_philo *philo);
void	multiple_thread_monitoring(t_data *data);

//MUTEX
int		init_mutex(t_data *data);
int		destroy_mutex(t_data *data);

// SIMULATION
void	*lone_philo_routine(void *void_philo);
void	*routine(void *void_philo);
int		simulation_start(t_data *data);
int		simulation_stop(t_data *data);

// UTILS
int		philo_atoi(const char *s);
int		are_digits(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
long	time_in_ms(void);
#endif