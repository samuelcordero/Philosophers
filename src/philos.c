#include "../inc/philosophers.h"
#include <pthread.h>

static void	*philos_routine(void *arg)
{
	(void)arg;
	return (NULL);
}

void	init_philos(t_sack *s)
{
	int	i;

	i = -1;
	s->philo_arr = malloc(sizeof(t_philo) * s->nbr_philos);
	if (!s->philo_arr)
		ft_error_exit("Couldn't allocate philos\n", 1);
	//init philos here and maybe mutexes before
	while (++i < s->nbr_philos)
		pthread_create(&s->philo_arr[i].tid, NULL, &philos_routine, NULL);
	i = -1;
	while (++i < s->nbr_philos)
		pthread_detach(s->philo_arr[i].tid);

}
