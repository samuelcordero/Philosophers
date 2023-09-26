/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 23:49:01 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/26 17:19:38 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_state(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->state_mut);
	result = philo->state;
	pthread_mutex_unlock(&philo->state_mut);
	return (result);
}

long	get_last_meal(t_philo *philo)
{
	long	result;

	pthread_mutex_lock(&philo->timer_mut);
	result = philo->last_meal;
	pthread_mutex_unlock(&philo->timer_mut);
	return (result);
}

int	get_meal_ctr(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->ctr_mut);
	result = philo->meal_ctr;
	pthread_mutex_unlock(&philo->ctr_mut);
	return (result);
}

char	take_forks(t_philo *philo)
{
	if (philo->left_fork != philo->right_fork)
	{
		pthread_mutex_lock(&philo->sack->fork_arr[philo->left_fork]);
		ft_printer(philo->sack, philo->id, FORK_MSG);
		pthread_mutex_lock(&philo->sack->fork_arr[philo->right_fork]);
		ft_printer(philo->sack, philo->id, FORK_MSG);
		return (1);
	}
	ft_printer(philo->sack, philo->id, FORK_MSG);
	set_state(philo, -1);
	return (0);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->sack->fork_arr[philo->left_fork]);
	pthread_mutex_unlock(&philo->sack->fork_arr[philo->right_fork]);
}
