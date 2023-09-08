/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:14 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/08 12:53:11 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	*philos_routine(void *arg)
{
	(void)arg;
	return (NULL);
}

static void	fill_philo(t_philo *philo, t_sack *sack, int id)
{
	philo->sack = sack;
	philo->id = id;
	philo->meal_ctr = 0;
	philo->last_meal = ft_time();
	if (pthread_mutex_init(&philo->eating_mtx, NULL))
		ft_error_exit("Couldn't init philo mutex\n", 1);
	pthread_create(&philo->tid, NULL, &philos_routine, NULL);
}

void	init_philos(t_sack *s)
{
	int	i;

	i = -1;
	s->fork_arr = malloc(sizeof(pthread_mutex_t) * s->nbr_philos);
	if (!s->fork_arr)
		ft_error_exit("Couldn`t allocate fork's mutexes\n", 1);
	while (++i < s->nbr_philos)
	{
		if (pthread_mutex_init(&s->fork_arr[i], NULL))
			ft_error_exit("Couldn't init fork mutex\n", 1);
	}
	s->philo_arr = malloc(sizeof(t_philo) * s->nbr_philos);
	if (!s->philo_arr)
		ft_error_exit("Couldn't allocate philos\n", 1);
	i = -1;
	while (++i < s->nbr_philos)
		fill_philo(&s->philo_arr[i], s, i);
	i = -1;
	while (++i < s->nbr_philos)
		pthread_detach(s->philo_arr[i].tid);
}
