/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:14 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/22 14:46:47 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	take_forks(t_philo *philo)
{
	if (philo->left_fork != philo->right_fork)
	{
		pthread_mutex_lock(&philo->sack->fork_arr[philo->left_fork]);
		ft_printer(philo->sack, philo->id, FORK_MSG);
		pthread_mutex_lock(&philo->sack->fork_arr[philo->right_fork]);
		ft_printer(philo->sack, philo->id, FORK_MSG);
		return (1);
	}
	return (0);
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->sack->fork_arr[philo->left_fork]);
	pthread_mutex_unlock(&philo->sack->fork_arr[philo->right_fork]);
}

static void	dinner_wakey_wakey(t_philo *philo)
{
	ft_printer(philo->sack, philo->id, EAT_MSG);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->meal_ctr++;
	philo->last_meal = ft_time();
	pthread_mutex_unlock(&philo->philo_mtx);
	ft_sleep(philo->sack->time_to_eat);
	release_forks(philo);
	ft_printer(philo->sack, philo->id, SLEEP_MSG);
	ft_sleep(philo->sack->time_to_sleep);
	ft_printer(philo->sack, philo->id, THINK_MSG);
	usleep(50);
}

void	*philos_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2)
		usleep(50);
	pthread_mutex_lock(&philo->sack->state_mutex);
	while (!philo->sack->state)
	{
		pthread_mutex_unlock(&philo->sack->state_mutex);
		if (take_forks(arg))
			dinner_wakey_wakey(philo);
		pthread_mutex_lock(&philo->sack->state_mutex);
	}
	return (pthread_mutex_unlock(&philo->sack->state_mutex), NULL);
}

/* static char	take_forks(t_philo *philo)
{
	char	s1;
	char	s2;

	s1 = 0;
	s2 = 0;
	pthread_mutex_lock(&philo->sack->fork_arr[philo->left_fork]);
	if (philo->sack->forks_states[philo->left_fork] == 0)
	{
		philo->sack->forks_states[philo->left_fork] = 1;
		s1 = 1;
		ft_printer(philo->sack, philo->id, FORK_MSG);
	}
	pthread_mutex_unlock(&philo->sack->fork_arr[philo->left_fork]);
	return (s1 & s2);
} */

/* static void	*philos_routine(void *arg)
{
	if (((t_philo *)arg)->id % 2)
		usleep(50);
	while (1)
	{
		if (take_forks((t_philo *)arg, ((t_philo *)arg)->id))
		{
			pthread_mutex_lock(&((t_philo *)arg)->eating_mtx);
			((t_philo *)arg)->last_meal = ft_time();
			((t_philo *)arg)->meal_ctr++;
			pthread_mutex_unlock(&((t_philo *)arg)->eating_mtx);
			ft_printer(((t_philo *)arg)->sack, ((t_philo *)arg)->id, EAT_MSG);
			ft_sleep(((t_philo *)arg)->sack->time_to_eat);
			release_forks(((t_philo *)arg)->sack, ((t_philo *)arg)->id);
			ft_printer(((t_philo *)arg)->sack, ((t_philo *)arg)->id, SLEEP_MSG);
			ft_sleep(((t_philo *)arg)->sack->time_to_sleep);
			ft_printer(((t_philo *)arg)->sack, ((t_philo *)arg)->id, THINK_MSG);
		}
		pthread_mutex_lock(&((t_philo *)arg)->sack->state_mutex);
		if (((t_philo *)arg)->sack->state)
			break ;
		pthread_mutex_unlock(&((t_philo *)arg)->sack->state_mutex);
	}s
	return (pthread_mutex_unlock(&((t_philo *)arg)->sack->state_mutex), NULL);
} */
