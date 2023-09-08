/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:16:51 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/08 16:06:18 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H
# include <pthread.h>

typedef struct s_sack t_sack;

typedef struct s_philo
{
	pthread_t		tid;
	pthread_mutex_t	eating_mtx;
	t_sack			*sack;
	int				meal_ctr;
	int				id;
	long			last_meal;
}	t_philo;

typedef struct s_sack
{
	t_philo			*philo_arr;
	pthread_mutex_t	*fork_arr;
	pthread_mutex_t	printer;
	pthread_mutex_t	state_mutex;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				nbr_philos;
	int				meals;
	long			start_time;
	char			state;
}	t_sack;

#endif
