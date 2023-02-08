
#include "../inc/philo.h"

void	red(void)
{
	printf("\033[1;31m");
}

void msg(char *s)
{
	red();
	printf("%s\n", s);
}

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
		return (msg("Wrong arg amount"), 0);
	if (!contains_digits(ac, av))
		return (msg("Only digits 0-9 are allowed"), 0);
	if (!contains_integers(ac, av))
		return(msg("Only 1-INTMAX are allowed"), 0);
	if (philo_atoi(av[1]) > PHILO_MAX) // do we need this check??
		return (msg("Change amt of philos"), 0);	
	return (1);
}
