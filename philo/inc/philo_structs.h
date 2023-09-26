/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:16:51 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/26 17:28:04 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H
# include <pthread.h>

typedef struct s_sack	t_sack;

typedef struct s_philo
{
	pthread_t		tid;
	pthread_mutex_t	state_mut;
	pthread_mutex_t	ctr_mut;
	pthread_mutex_t	timer_mut;
	int				state;
	int				meal_ctr;
	int				id;
	int				left_fork;
	int				right_fork;
	long			last_meal;
	t_sack			*sack;
}	t_philo;

typedef struct s_sack
{
	t_philo			*philo_arr;
	pthread_mutex_t	*fork_arr;
	pthread_mutex_t	printer_mutex;
	pthread_mutex_t	state_mutex;
	int				state;
	int				time_to_sleep;
	int				time_to_eat;
	int				t2d;
	int				nbr_philos;
	int				meals;
	int				philos_done;
	long			start_time;
	char			print_ok;
}	t_sack;

#endif
