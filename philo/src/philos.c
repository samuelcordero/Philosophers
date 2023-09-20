/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:14 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/20 16:20:18 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	take_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id % philo->sack->nbr_philos;
	right = (philo->id  + 1) % philo->sack->nbr_philos;
	if (left < right)
	{
		pthread_mutex_lock(&philo->sack->fork_arr[left]);
		ft_printer(philo->sack, philo->id, FORK_MSG);
		pthread_mutex_lock(&philo->sack->fork_arr[right]);
		ft_printer(philo->sack, philo->id, FORK_MSG);
		return (1);
	}
	else if (left != right)
	{
		pthread_mutex_lock(&philo->sack->fork_arr[right]);
		ft_printer(philo->sack, philo->id, FORK_MSG);
		pthread_mutex_lock(&philo->sack->fork_arr[left]);
		ft_printer(philo->sack, philo->id, FORK_MSG);
		return (1);
	}
	return (0);
}

static void	release_forks(t_sack *sack, int id)
{
	pthread_mutex_unlock(&sack->fork_arr[id % sack->nbr_philos]);
	pthread_mutex_unlock(&sack->fork_arr[(id + 1) % sack->nbr_philos]);
}

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
	}
	return (pthread_mutex_unlock(&((t_philo *)arg)->sack->state_mutex), NULL);
} */

static void	*philos_routine(void *arg)
{
	while (1)
	{
		if (((t_philo *)arg)->philo_state == 0)
			((t_philo *)arg)->philo_state = take_forks(arg);
		else if (((t_philo *)arg)->philo_state == 1)
		{
			((t_philo *)arg)->last_meal = ft_time();
			((t_philo *)arg)->meal_ctr++;
			ft_printer(((t_philo *)arg)->sack, ((t_philo *)arg)->id, EAT_MSG);
			ft_sleep(((t_philo *)arg)->sack->time_to_eat);
			release_forks(((t_philo *)arg)->sack, ((t_philo *)arg)->id);
			((t_philo *)arg)->philo_state++;
		}
		else if (((t_philo *)arg)->philo_state == 2)
		{
			ft_printer(((t_philo *)arg)->sack, ((t_philo *)arg)->id, SLEEP_MSG);
			ft_sleep(((t_philo *)arg)->sack->time_to_sleep);
			ft_printer(((t_philo *)arg)->sack, ((t_philo *)arg)->id, THINK_MSG);
			((t_philo *)arg)->philo_state = 0;
		}
		if (millis_since(((t_philo *)arg)->last_meal) > ((t_philo *)arg)->sack->time_to_die)
		{
			ft_print_dead(((t_philo *)arg)->sack, ((t_philo *)arg)->id);
			break ;
		}
	}
	return (NULL);
}

static int	fill_philo(t_philo *philo, t_sack *sack, int id)
{
	memset(philo, 0, sizeof(t_philo));
	philo->sack = sack;
	philo->id = id;
	philo->last_meal = ft_time();
	if (pthread_mutex_init(&philo->philo_mtx, NULL))
		return (ft_error_exit("Couldn't init philo mutex\n", 1));
	return (0);
}

int	init(t_sack *s)
{
	int	i;

	i = -1;
	s->fork_arr = malloc(sizeof(pthread_mutex_t) * s->nbr_philos);
	s->forks_states = malloc(s->nbr_philos);
	if (!s->forks_states)
		return (ft_error_exit("Couldn't init fork state array\n", 1));
	memset(s->forks_states, 0, s->nbr_philos);
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
		pthread_create(&s->philo_arr[i].tid, NULL,
			&philos_routine, &s->philo_arr[i]);
	//checker(s);
	i = -1;
	while (++i < s->nbr_philos)
		pthread_join(s->philo_arr[i].tid, NULL);
	return (0);
}
