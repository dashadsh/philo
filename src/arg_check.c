
#include "../inc/philo.h"

int	contains_digits(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!are_digits(av[i]))
			return (0);
	}
	return (1);
}

int	contains_integers(int ac, char **av)
{
	int	i;
	int	nb;

	i = 0;
	while (++i < ac)
	{
		nb = philo_atoi(av[i]);
		if (nb <= 0)
			return (0);
	}
	return (1);
}

int	valid_input(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (msg("wrong arg amount"), 0);
	if (!contains_digits(ac, av))
		return (msg("digits 0-9 allowed"), 0);
	if (!contains_integers(ac, av))
		return(msg("int 1-INTMAX allowed"), 0);
	if (philo_atoi(av[1]) > PHILO_MAX) // do we need this check??
		return (msg("max 200 philos"), 0);	
	return (1);
}
