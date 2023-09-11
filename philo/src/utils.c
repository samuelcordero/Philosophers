/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:25 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/11 18:27:26 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

int	ft_error_exit(char *str, int n)
{
	while (*str)
		write(2, (str++), 1);
	return (n);
}

int	ft_space_or_digit(char c)
{
	if ((c >= '0' && c <= '9') || c == ' '
		|| c == '\v' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\r') && str[i])
		++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		if (res > INT_MAX)
			return (ft_error_exit(ARG2BIG, -1));
		++i;
	}
	return (res);
}

void	ft_printer(t_sack *sack, int id, char *action)
{
	pthread_mutex_lock(&sack->printer);
	pthread_mutex_lock(&sack->state_mutex);
	if (!sack->state)
		printf("%ld %d %s\n",
			millis_since(sack->start_time), id + 1, action);
	pthread_mutex_unlock(&sack->state_mutex);
	pthread_mutex_unlock(&sack->printer);
	usleep(50);
}

void	ft_print_dead(t_sack *sack, int id, char *action)
{
	long	tstamp;

	tstamp = ft_time() - sack->start_time;
	printf("%ld %d %s\n", tstamp, id + 1, action);
}
