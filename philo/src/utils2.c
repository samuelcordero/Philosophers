/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:19 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/27 12:16:17 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

long	millis_since(long t)
{
	return (ft_time() - t);
}

void	ft_sleep(long t)
{
	long	end;

	end = ft_time() + t;
	while (ft_time() < end)
		usleep(700);
}

void	killall(t_sack *sack)
{
	int	i;

	i = -1;
	while (++i < sack->nbr_philos)
		set_state(&sack->philo_arr[i], -1);
}

int	check_str_posint(char *str)
{
	while (*str)
	{
		if (!ft_space_or_digit(*str))
			return (ft_error_exit(BAD_ARGS, 1));
		++str;
	}
	return (0);
}
