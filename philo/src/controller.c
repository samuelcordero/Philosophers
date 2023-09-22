/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:03:21 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/22 14:20:25 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_philo(int i, t_sack *sack)
{
	pthread_mutex_lock(&sack->philo_arr[i].philo_mtx);
	if (sack->philo_arr[i].meal_ctr >= sack->meals)
		sack->philos_done++;
	pthread_mutex_unlock(&sack->philo_arr[i].philo_mtx);
}

static int	checker(t_sack *sack)
{
	int	i;

	pthread_mutex_lock(&sack->state_mutex);
	while (!sack->state)
	{
		pthread_mutex_unlock(&sack->state_mutex);
		sack->philos_done = 0;
		i = -1;
		while (++i < sack->nbr_philos)
			check_philo(i, sack);
		pthread_mutex_lock(&sack->state_mutex);
		if (sack->philos_done == sack->nbr_philos)
			sack->state = 1;
	}
	pthread_mutex_unlock(&sack->state_mutex);
	i = -1;
	while (++i < sack->nbr_philos)
		pthread_join(sack->philo_arr[i].tid, NULL);
	return (0);
}

static int	fill_philo(t_philo *philo, t_sack *sack, int id)
{
	memset(philo, 0, sizeof(t_philo));
	philo->sack = sack;
	philo->id = id;
	philo->last_meal = ft_time();
	philo->left_fork = philo->id % philo->sack->nbr_philos;
	philo->right_fork = (philo->id + 1) % philo->sack->nbr_philos;
	if (philo->id == philo->sack->nbr_philos - 1)
	{
		philo->right_fork = philo->left_fork;
		philo->left_fork = 0;
	}
	if (pthread_mutex_init(&philo->philo_mtx, NULL))
		return (ft_error_exit("Couldn't init philo mutex\n", 1));
	return (0);
}

int	init(t_sack *s)
{
	int	i;

	i = -1;
	s->fork_arr = malloc(sizeof(pthread_mutex_t) * s->nbr_philos);
	if (!s->fork_arr)
		return (ft_error_exit("Couldn`t allocate fork's mutexes\n", 1));
	while (++i < s->nbr_philos)
		if (pthread_mutex_init(&s->fork_arr[i], NULL))
			return (ft_error_exit("Couldn't init fork mutex\n", 1));
	s->philo_arr = malloc(sizeof(t_philo) * s->nbr_philos);
	if (!s->philo_arr)
		return (ft_error_exit("Couldn't allocate philos\n", 1));
	i = -1;
	while (++i < s->nbr_philos)
		if (fill_philo(&s->philo_arr[i], s, i))
			return (1);
	i = -1;
	while (++i < s->nbr_philos)
	{
		pthread_create(&s->philo_arr[i].tid, NULL,
			&philos_routine, &s->philo_arr[i]);
		usleep(5);
	}
	return (checker(s));
}
