/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:14 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/11 18:26:59 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_sack *sack, int id)
{
	int	left;
	int	right;

	left = id % sack->nbr_philos;
	right = (id + 1) % sack->nbr_philos;
	if (left < right)
	{
		pthread_mutex_lock(&sack->fork_arr[left]);
		ft_printer(sack, id, FORK_MSG);
		pthread_mutex_lock(&sack->fork_arr[right]);
		ft_printer(sack, id, FORK_MSG);
	}
	else
	{
		pthread_mutex_lock(&sack->fork_arr[right]);
		ft_printer(sack, id, FORK_MSG);
		pthread_mutex_lock(&sack->fork_arr[left]);
		ft_printer(sack, id, FORK_MSG);
	}
}

static void	release_forks(t_sack *sack, int id)
{
	int	left;
	int	right;

	left = id % sack->nbr_philos;
	right = (id + 1) % sack->nbr_philos;
	if (left < right)
	{
		pthread_mutex_unlock(&sack->fork_arr[left]);
		pthread_mutex_unlock(&sack->fork_arr[right]);
	}
	else
	{
		pthread_mutex_unlock(&sack->fork_arr[right]);
		pthread_mutex_unlock(&sack->fork_arr[left]);
	}
}

static void	*philos_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2)
		usleep(50);
	pthread_mutex_lock(&philo->sack->state_mutex);
	while (!philo->sack->state && philo->meal_ctr < philo->sack->meals)
	{
		pthread_mutex_unlock(&philo->sack->state_mutex);
		take_forks(philo->sack, philo->id);
		pthread_mutex_lock(&philo->eating_mtx);
		philo->last_meal = ft_time();
		pthread_mutex_unlock(&philo->eating_mtx);
		ft_printer(philo->sack, philo->id, EATING_MSG);
		ft_sleep(philo->sack->time_to_eat);
		release_forks(philo->sack, philo->id);
		ft_printer(philo->sack, philo->id, SLEEPING_MSG);
		ft_sleep(philo->sack->time_to_sleep);
		ft_printer(philo->sack, philo->id, THINKING_MSG);
		pthread_mutex_lock(&philo->sack->state_mutex);
		philo->meal_ctr++;
	}
	philo->sack->philos_done++;
	pthread_mutex_unlock(&philo->sack->state_mutex);
	return (NULL);
}

static int	fill_philo(t_philo *philo, t_sack *sack, int id)
{
	philo->sack = sack;
	philo->id = id;
	philo->meal_ctr = 0;
	philo->last_meal = ft_time();
	if (pthread_mutex_init(&philo->eating_mtx, NULL))
		return (ft_error_exit("Couldn't init philo mutex\n", 1));
	pthread_create(&philo->tid, NULL, &philos_routine, philo);
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
	{
		if (pthread_mutex_init(&s->fork_arr[i], NULL))
			return (ft_error_exit("Couldn't init fork mutex\n", 1));
	}
	s->philo_arr = malloc(sizeof(t_philo) * s->nbr_philos);
	if (!s->philo_arr)
		return (ft_error_exit("Couldn't allocate philos\n", 1));
	i = -1;
	while (++i < s->nbr_philos)
		if (fill_philo(&s->philo_arr[i], s, i))
			return (1);
	i = -1;
	while (++i < s->nbr_philos)
		pthread_detach(s->philo_arr[i].tid);
	checker(s);
	return (0);
}
