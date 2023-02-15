

#include "../inc/philo.h"

//actions for current philo
void	philo_eating(t_philo *philo) //STATIC????
{
	pthread_mutex_lock(&(philo->data->forks[philo->l_fork]));
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->data->forks[philo->r_fork]));
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	smart_sleep(philo, philo->data->time_to_eat); //CHECK IT!
	//usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&(philo->data->do_lock));
	philo->ate++; // CHANGING LOCAL STUFF
	philo->last_meal = time_in_ms(); // how to get right time??
	pthread_mutex_unlock(&(philo->data->do_lock));
	pthread_mutex_unlock(&(philo->data->forks[philo->l_fork]));
	pthread_mutex_unlock(&(philo->data->forks[philo->r_fork]));
	// t_data	*data;

	// data = philo->data;
	// pthread_mutex_lock(&(data->forks[philo->l_fork]));
	// print_status(philo, "has taken a fork");
	// pthread_mutex_lock(&(data->forks[philo->r_fork]));
	// print_status(philo, "has taken a fork");
	// print_status(philo, "is eating");
	// smart_sleep(philo, data->time_to_eat);
	// //usleep(data->time_to_eat * 1000);
	// pthread_mutex_lock(&(data->do_lock));
	// philo->last_meal = time_in_ms(); // how to get right time
	// philo->ate++; // CHANGING LOCAL STUFF
	// pthread_mutex_unlock(&(data->do_lock));
	// pthread_mutex_unlock(&(data->forks[philo->l_fork]));
	// pthread_mutex_unlock(&(data->forks[philo->r_fork]));
}

void	philo_sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	smart_sleep(philo, philo->data->time_to_sleep);
	//usleep(data->time_to_sleep * 1000);
}

void	philo_thinking(t_philo *philo)
{
	print_status(philo, "is thinking");
}
