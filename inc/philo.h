/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:24:31 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/02/15 20:12:07 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h> 
# include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE malloc
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
#	include <unistd.h>

# define PHILO_MAX 200

// timestamp_in_ms X has taken a fork 
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died

typedef struct s_philo	t_philo;

typedef struct s_data
{
	long starttime;
	int	n_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int n_must_eat;
	int fed; //count in single killer
	int sim_stop; // bool, philos are acting until it !=1
	t_philo	*philo;
	pthread_mutex_t	*forks; //variable to save mutexes 
	pthread_mutex_t	write_lock;
	pthread_mutex_t do_lock;
	pthread_mutex_t sim_stop_lock;
} t_data;


//each philo is a thread
typedef struct s_philo
{
	pthread_t	philo_tid;
	int id;
	int ate; // will be needed to count amt of meals
	int l_fork; // id of fork which philo will take first
	int r_fork; // used to have an ID of fork mutex
	long last_meal; // = 0 default
	t_data *data;
} t_philo;

// MAIN
int	main(int ac, char **av);

// ARG CHECK
int	contains_digits(int ac, char **av);
int contains_integers(int ac, char **av);
int	valid_input(int ac, char **av);

// INIT
void extract_args(t_data *data, int ac, char **av);
int init_philo(t_data *data);
int	init_data(t_data *data, int ac, char **av);

//MUTEX
int	init_mutex(t_data *data);
int	destroy_mutex(t_data *data);

// UTILS
int		philo_atoi(const char *s);
int		are_digits(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
long	time_in_ms(void);

// LONE_PHILO
void	*lone_philo_routine(void *void_data);
int	simulation_for_one(t_data *data);

// MESSAGE
void	red(void);
void msg(char *s);


void	smart_sleep(t_philo *philo, long ms);
void	print_status(t_philo *philo, char *s);

void	philo_eating(t_philo *philo);
void	philo_sleeping(t_philo *philo);
void	philo_thinking(t_philo *philo);

// void	*routine2(t_philo *philo);
void	*routine(void *void_philo);
int	simulation_start(t_data *data);
int	simulation_stop(t_data *data);

int	check_sim_stop(t_philo *philo);
int	check_sim_stop(t_philo *philo);
int	sim_stop(t_philo *philo, int i);

// FREE
void	free_all(t_data *data);
#endif