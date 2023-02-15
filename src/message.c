
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

// void	print_status(t_data *data, int id, int status)
// {
// 	long	t;

// 	pthread_mutex_lock(&(data->write_lock));
// 	t = time_in_ms() - data->starttime;
// 	// if (!(data->death_flag))
// 	// {
// 		if (action == FORK)
// 			printf("%lli Philosopher %i has taken a fork.\n", ts, id + 1);
// 		else if (action == EATING)
// 			printf("%lli Philosopher %i is eating.\n", ts, id + 1);
// 		else if (action == SLEEPING)
// 			printf("%lli Philosopher %i is sleeping.\n", ts, id + 1);
// 		else if (action == THINKING)
// 			printf("%lli Philosopher %i is thinking.\n", ts, id + 1);
// 		else if (action == DEAD)
// 			printf("%lli Philosopher %i died.\n", ts, id + 1);
// 	// }
// 	pthread_mutex_unlock(&(state->write));
// 	return ;
// }