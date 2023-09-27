/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:03:21 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/27 12:24:29 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	end_sim(t_sack *sack)
{
	killall(sack);
	pthread_mutex_lock(&sack->printer_mutex);
	sack->print_ok = 1;
	pthread_mutex_unlock(&sack->printer_mutex);
	sack->state = 1;
}

void	checker(t_sack *sack)
{
	int	i;
	int	done;

	i = -1;
	done = 0;
	while (++i < sack->nbr_philos && sack->state == 0)
	{
		if (millis_since(get_last_meal(&sack->philo_arr[i])) > sack->t2d)
		{
			if (get_state(&sack->philo_arr[i]) != 1)
			{
				ft_print_dead(sack, i);
				killall(sack);
				sack->state = 1;
				break ;
			}
		}
		if (get_meal_ctr(&sack->philo_arr[i]) >= sack->meals)
			done++;
	}
	if (done == sack->nbr_philos && sack->state == 0)
		end_sim(sack);
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
	if (pthread_mutex_init(&philo->state_mut, NULL)
		|| pthread_mutex_init(&philo->ctr_mut, NULL)
		|| pthread_mutex_init(&philo->timer_mut, NULL))
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
	return (0);
}

int	start(t_sack *sack)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&sack->state_mutex);
	while (++i < sack->nbr_philos)
		if (pthread_create(&sack->philo_arr[i].tid, NULL,
				&philos_routine, &sack->philo_arr[i]))
			return (1);
	sack->start_time = ft_time();
	pthread_mutex_unlock(&sack->state_mutex);
	while (sack->state == 0)
		checker(sack);
	i = -1;
	sack->start_time = ft_time();
	while (++i < sack->nbr_philos)
		pthread_join(sack->philo_arr[i].tid, NULL);
	return (0);
}
