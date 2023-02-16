
#include "../inc/philo.h"


// void	red(void)
// {
// 	printf("\033[1;31m");
// }

// void	yellow(void)
// {
// 	printf("\033[1;33m");
// }

// void	green(void)
// {
// 	printf("\033[0;32m");
// }

// void	white(void)
// {
// 	printf("\033[37m");
// }

// void	blue(void)
// {
// 	printf("\033[0;34m");
// }

// void	purple()
// {
// 	printf("\033[0;35m");
// }


// void	print_status(t_philo *philo, char *s)
// {
// 	pthread_mutex_lock(&(philo->data->write_lock));
// 	if (!check_sim_stop(philo))
// 	{
// 		printf("%ld ", time_in_ms() - philo->data->starttime);
// 		printf("%i ", philo->id + 1);
// 		printf("%s\n", s);
// 	}
// 	pthread_mutex_unlock(&(philo->data->write_lock));
// }

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->write_lock));
	if (!check_sim_stop(philo))
	{
		printf("\033[1;33m");
		printf("%ld ", time_in_ms() - philo->data->starttime);
		printf("%i ", philo->id + 1);
		printf("has taken a fork\n");
	}
	pthread_mutex_unlock(&(philo->data->write_lock));
}

void	print_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->write_lock));
	if (!check_sim_stop(philo))
	{
		printf("\033[0;32m");
		printf("%ld ", time_in_ms() - philo->data->starttime);
		printf("%i ", philo->id + 1);
		printf("is eating\n");
	}
	pthread_mutex_unlock(&(philo->data->write_lock));
}

void	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->write_lock));
	if (!check_sim_stop(philo))
	{
		printf("\033[0;34m");
		printf("%ld ", time_in_ms() - philo->data->starttime);
		printf("%i ", philo->id + 1);
		printf("is sleeping\n");
	}
	pthread_mutex_unlock(&(philo->data->write_lock));
}

void	print_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->write_lock));
	if (!check_sim_stop(philo))
	{
		printf("\033[0;35m");
		printf("%ld ", time_in_ms() - philo->data->starttime);
		printf("%i ", philo->id + 1);
		printf("is thinking\n");
	}
	pthread_mutex_unlock(&(philo->data->write_lock));
}

void	print_die(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->write_lock));
	if (!check_sim_stop(philo))
	{
		printf("\033[1;31m");
		printf("%ld ", time_in_ms() - philo->data->starttime);
		printf("%i ", philo->id + 1);
		printf("died\n");
	}
	pthread_mutex_unlock(&(philo->data->write_lock));
}