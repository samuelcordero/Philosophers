/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:07 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/10 22:20:46 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

static void	check_str_posint(char *str)
{
	while (*str)
	{
		if (!ft_space_or_digit(*str))
			ft_error_exit(BAD_ARGS, 2);
		++str;
	}
}

static t_sack	check_args(int argc, char **argv)
{
	t_sack	res;

	res.philos_done = 0;
	if (argc < 5 || argc > 6)
		ft_error_exit(BAD_ARGS_NBR, 1);
	while (argv[++res.philos_done])
		check_str_posint(argv[res.philos_done]);
	res.nbr_philos = ft_atoi(argv[1]);
	res.time_to_die = ft_atoi(argv[2]);
	res.time_to_eat = ft_atoi(argv[3]);
	res.time_to_sleep = ft_atoi(argv[4]);
	res.meals = INT_MAX;
	res.state = 0;
	res.philos_done = 0;
	res.start_time = ft_time();
	if (argv[5])
		res.meals = ft_atoi(argv[5]);
	if (pthread_mutex_init(&res.printer, NULL))
		ft_error_exit("Couldn't init printer mutex\n", 1);
	if (pthread_mutex_init(&res.state_mutex, NULL))
		ft_error_exit("Couldn't init state mutex\n", 1);
	return (res);
}

int	main(int argc, char **argv)
{
	t_sack	sack;

	sack = check_args(argc, argv);
	printf("philos: %i\ntime2die %i\ntime2eat %i\ntime2sleep %i\ntotal meals %i\n",
		sack.nbr_philos, sack.time_to_die, sack.time_to_eat,
		sack.time_to_sleep, sack.meals);
	init_philos(&sack);
	return (0);
}
