/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:14 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/26 01:28:14 by sacorder         ###   ########.fr       */
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
	if (take_forks(philo))
	{
		set_last_meal(philo);
		ft_printer(philo->sack, philo->id, EAT_MSG);
		inc_meal_ctr(philo);
		ft_sleep(philo->sack->time_to_eat);
		release_forks(philo);
		return (0);
	}
	return (1);
}

void	*philos_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2)
		usleep(50);
	while (get_state(philo) >= 0)
	{
		if (eat(philo))
			break ;
		if (get_state(philo) < 0)
			break ;
		ft_printer(philo->sack, philo->id, SLEEP_MSG);
		ft_sleep(philo->sack->time_to_sleep);
		if (get_state(philo) < 0)
			break ;
		ft_printer(philo->sack, philo->id, THINK_MSG);
	}
	return (NULL);
}
