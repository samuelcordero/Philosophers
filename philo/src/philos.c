/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:14 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/15 12:35:54 by sacorder         ###   ########.fr       */
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
	pthread_mutex_unlock(&sack->fork_arr[id % sack->nbr_philos]);
	pthread_mutex_unlock(&sack->fork_arr[(id + 1) % sack->nbr_philos]);
}

static void	*philos_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2)
		usleep(50);
	while (1)
	{
		take_forks(philo->sack, philo->id);
		pthread_mutex_lock(&philo->eating_mtx);
		philo->last_meal = ft_time();
		philo->meal_ctr++;
		ft_printer(philo->sack, philo->id, EATING_MSG);
		pthread_mutex_unlock(&philo->eating_mtx);
		ft_sleep(philo->sack->time_to_eat);
		release_forks(philo->sack, philo->id);
		ft_printer(philo->sack, philo->id, SLEEPING_MSG);
		ft_sleep(philo->sack->time_to_sleep);
		ft_printer(philo->sack, philo->id, THINKING_MSG);
		pthread_mutex_lock(&philo->sack->state_mutex);
		if (philo->sack->state)
			break ;
		pthread_mutex_unlock(&philo->sack->state_mutex);
	}
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
		usleep(50);
	}
	checker(s);
	i = -1;
	while (++i < s->nbr_philos)
		pthread_join(s->philo_arr[i].tid, NULL);
	return (0);
}
