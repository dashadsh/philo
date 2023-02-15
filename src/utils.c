
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

int	are_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
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

long	time_in_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	//printf("%ld\n", t.tv_sec * 1000 + t.tv_usec / 1000);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}