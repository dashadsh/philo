/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:24:31 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/02/08 13:16:14 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h> 
# include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
# include <pthread.h>
# include <stdbool.h>

# define PHILO_MAX 250


// "input: ./philo <number_of_philosophers> 
//<time_to_die> <time_to_eat> <time_to_sleep> 
// [number_of_times_each_philosopher_must_eat]\n"

// ERROR MESSAGES

# define ARG_AMT "Error: amount of arguments should be 4 or 5\n"
# define INPUT "Wrong input, check if the data is valid / amt of philo is allowed\n"
# define ALLOC "Error: couldn't allocate memory\n"

// timestamp_in_ms X has taken a fork 
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died

typedef struct s_philo	t_philo;

typedef struct s_data
{
	// time_t			start_time;
	int		n_philo;
	int		time_to_die; // time_t
	int		time_to_eat;
	int		time_to_sleep;
	// int		n_to_eat;
	
	// int	dead; //
	// int all_ate; // ???
	

	// pthread_mutex_t *forks_mutex; // all mutexes stored here

	// bool	someone_died;
	// bool	stop_simulation;
	
	// int		num_already_ate;
	// // pthread_mutex_t	is_dead_lock
	
	// pthread_mutex_t	printf_lock;

	// t_philo		*philo;

} t_data;

typedef struct s_philo
{
	// int		philo_id;
	// int		*l_fork;
	// int		*r_fork;
	
	// t_table 	*table;
	
} t_philo;


int	main(int ac, char **av);

void init_data(t_data *data, int ac, char **av);
int	init_mutex(t_data *data);
int	init_all(t_data *data, int ac, char **av);


int	valid_input(int ac, char **av);
	// four_five_args(int ac);
int	digits_only(char *str);
void	err(char *s);

// utils
int	philo_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

// error_check

#endif