
#include "../inc/philo.h"

int	philo_atoi(const char *s)
{
	long long int	nb;

	nb = 0;
	while (*s >= '0' && *s <= '9')
	{
		nb = (nb * 10) + *s - '0';
		s++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}


void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	*str;

	if (count >= 4294967295 || size >= 4294967295)
		return (NULL);
	str = malloc(count * size);
	if (!str)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}
