/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:03:21 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/10 22:18:40 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	checker(t_sack *sack)
{
	int	i;

	pthread_mutex_lock(&sack->state_mutex);
	while (!sack->state && sack->philos_done < sack->nbr_philos)
	{
		i = -1;
		while (++i < sack->nbr_philos && !sack->state)
		{
			pthread_mutex_lock(&sack->philo_arr[i].eating_mtx);
			if (millis_since(sack->philo_arr[i].last_meal) > sack->time_to_die
				&& sack->philo_arr[i].meal_ctr < sack->meals)
			{
				ft_printer(sack, i, DEAD_MSG);
				sack->state = !sack->state;
			}
			pthread_mutex_unlock(&sack->state_mutex);
			pthread_mutex_unlock(&sack->philo_arr[i].eating_mtx);
			pthread_mutex_lock(&sack->state_mutex);
		}
	}
	pthread_mutex_unlock(&sack->state_mutex);
	exit (0);
}
