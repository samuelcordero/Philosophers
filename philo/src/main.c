/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:07 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/27 12:16:52 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	recheck(t_sack *res)
{
	if (res->nbr_philos == -1 || res->t2d == -1 || res->meals == -1
		|| res->time_to_sleep == -1 || res->time_to_eat == -1)
		return (1);
	return (0);
}

int	destroy(t_sack *sack)
{
	int	i;

	pthread_mutex_destroy(&sack->state_mutex);
	pthread_mutex_destroy(&sack->printer_mutex);
	i = -1;
	while (++i < sack->nbr_philos)
		pthread_mutex_destroy(&sack->fork_arr[i]);
	i = -1;
	while (++i < sack->nbr_philos)
	{
		pthread_mutex_destroy(&sack->philo_arr[i].state_mut);
		pthread_mutex_destroy(&sack->philo_arr[i].timer_mut);
		pthread_mutex_destroy(&sack->philo_arr[i].ctr_mut);
	}
	free(sack->philo_arr);
	free(sack->fork_arr);
	return (0);
}

static int	fill_sack(char **argv, t_sack *res)
{
	res->philos_done = 0;
	while (argv[++res->philos_done])
		if (check_str_posint(argv[res->philos_done]))
			return (1);
	res->nbr_philos = ft_atoi(argv[1]);
	res->t2d = ft_atoi(argv[2]);
	res->time_to_eat = ft_atoi(argv[3]);
	res->time_to_sleep = ft_atoi(argv[4]);
	res->meals = INT_MAX;
	res->philos_done = 0;
	res->start_time = ft_time();
	if (argv[5])
		res->meals = ft_atoi(argv[5]);
	if (pthread_mutex_init(&res->printer_mutex, NULL))
		return (ft_error_exit("Couldn't init printer state mutex\n", 1));
	if (pthread_mutex_init(&res->state_mutex, NULL))
		return (ft_error_exit("Couldn't init state mutex\n", 1));
	return (recheck(res));
}

int	main(int argc, char **argv)
{
	t_sack	sack;

	memset(&sack, 0, sizeof(sack));
	if (argc < 5 || argc > 6)
		return (ft_error_exit(BAD_ARGS_NBR, 1));
	if (fill_sack(argv, &sack))
		return (1);
	if (init(&sack))
		return (1);
	if (start(&sack))
		return (1);
	return (destroy(&sack));
}

/*
		printf("philos: %i\ntime2die %i\ntime2eat %i\ntime2sleep %i\ntotal meals %i\n",
		sack.nbr_philos, sack.time_to_die, sack.time_to_eat,
		sack.time_to_sleep, sack.meals);
 */
