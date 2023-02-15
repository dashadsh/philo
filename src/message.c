
#include "../inc/philo.h"

void	red(void)
{
	printf("\033[1;31m");
}

void	msg(char *s)
{
	red();
	printf("%s\n", s);
}

