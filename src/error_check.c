/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:52:28 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/01/30 18:58:22 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_digit(char *str) // static?
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	err_msg(char *s) 
{
	printf(s); // format string is not a string literal (potentially insecure) [-Wformat-security]
} // treat the string as an argument to avoid this


int valid_input(int ac, char **av)
{
	if (ac - 1 < 4 || ac - 1 > 5)
		return (err_msg(ERR_INPUT), 0);
	return(1);
}