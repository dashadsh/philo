

#include "../inc/philo.h"



int	main(int ac, char **av)
{
	t_data	*data;

	if (!valid_input(ac, av))
		return (msg("input invalid"), 1);

	data = malloc(1 * sizeof(t_data));
	if (!data)
		return (msg("ft_calloc (t_data *data) error"), 1);
	if (!init_data(data, ac, av))
		return (msg("init_data error"), 1); // free
	if (!simulation_start(data))
		return (msg("simulation_start error"), 1);
	if (!simulation_stop(data))
		return (msg("simulation_stop error"), 1);
	free_all(data);
	return (0);
}