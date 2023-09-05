#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H
# include <pthread.h>

typedef struct s_sack t_sack;

typedef struct s_philo
{
	pthread_t				tid;
	pthread_mutex_t	eating_mtx;
	t_sack					*sack;
	int							meal_ctr;
	int							id;
	long						last_meal;
}	t_philo;

typedef struct s_sack
{
	t_philo					*philo_arr;
	pthread_mutex_t	*mutex_arr;
	int							time_to_sleep;
	int							time_to_eat;
	int							time_to_die;
	int							nbr_philos;
	int							meals;
	long						start_time;
}	t_sack;

#endif
