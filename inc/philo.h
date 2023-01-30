/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:24:31 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/01/30 18:58:47 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h> 
# include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE

# define ERR_INPUT "input: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"

int	main(int ac, char **av);

int valid_input(int ac, char **av);
void	err_msg(char *s);
int	is_digit(char *str);


// utils
int	ft_atoi(const char *str);

// error_check

#endif