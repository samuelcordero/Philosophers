#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H
# include <pthread.h>

typedef struct s_philo
{
	pthread_t	*p;
}	t_philo;

typedef struct s_sack
{
	t_philo					*philo_arr;
	pthread_mutex_t	*mutex_arr;
	int							time_to_sleep;
	int							time_to_eat;
	int							time_to_die;
	int							nbr_of_philos;
	int							meals;
}	t_sack;

#endif
