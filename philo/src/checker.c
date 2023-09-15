/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:03:21 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/15 12:39:13 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	checker(t_sack *sack)
{
	int	i;

	pthread_mutex_lock(&sack->state_mutex);
	while (!sack->state && sack->philos_done < sack->nbr_philos)
	{
		sack->philos_done = 0;
		i = -1;
		while (++i < sack->nbr_philos && !sack->state)
		{
			pthread_mutex_lock(&sack->philo_arr[i].eating_mtx);
			if (millis_since(sack->philo_arr[i].last_meal) >= sack->time_to_die)
			{
				ft_print_dead(sack, i, DEAD_MSG);
				sack->state = !sack->state;
			}
			if (sack->philo_arr[i].meal_ctr >= sack->meals)
				sack->philos_done++;
			pthread_mutex_unlock(&sack->state_mutex);
			pthread_mutex_unlock(&sack->philo_arr[i].eating_mtx);
			usleep(50);
			pthread_mutex_lock(&sack->state_mutex);
		}
		if (sack->philos_done == sack->nbr_philos)
		{
			sack->state = !sack->state;
			break ;
		}
	}
	pthread_mutex_unlock(&sack->state_mutex);
	return (0);
}
