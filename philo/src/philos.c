/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:14 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/27 02:25:18 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_state(t_philo *philo, int val)
{
	pthread_mutex_lock(&philo->state_mut);
	philo->state = val;
	pthread_mutex_unlock(&philo->state_mut);
}

void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->timer_mut);
	philo->last_meal = ft_time();
	pthread_mutex_unlock(&philo->timer_mut);
}

void	inc_meal_ctr(t_philo *philo)
{
	pthread_mutex_lock(&philo->ctr_mut);
	philo->meal_ctr++;
	pthread_mutex_unlock(&philo->ctr_mut);
}

static int	eat(t_philo *philo)
{
	if (get_state(philo) >= 0)
	{
		if (take_forks(philo))
		{
			if (get_state(philo) >= 0)
				set_state(philo, 1);
			set_last_meal(philo);
			ft_printer(philo->sack, philo->id, EAT_MSG);
			ft_sleep(philo->sack->time_to_eat);
			release_forks(philo);
			inc_meal_ctr(philo);
			if (get_state(philo) >= 0)
				set_state(philo, 0);
			return (0);
		}
	}
	return (1);
}

void	*philos_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(&philo->sack->state_mutex);
	pthread_mutex_unlock(&philo->sack->state_mutex);
	if (philo->id % 2)
		ft_sleep(50);
	while (get_state(philo) >= 0)
	{
		if (eat(philo))
			break ;
		ft_printer(philo->sack, philo->id, SLEEP_MSG);
		ft_sleep(philo->sack->time_to_sleep);
		ft_printer(philo->sack, philo->id, THINK_MSG);
		ft_sleep(1);
	}
	return (NULL);
}
