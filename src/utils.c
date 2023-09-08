/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:25 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/08 15:59:28 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_error_exit(char *str, int n)
{
	while (*str)
		write(2, (str++), 1);
	exit(n);
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
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\r') && str[i])
		++i;
	while(str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		++i;
	}
	return (res);
}

void	ft_printer(t_sack *sack, int id, char *action)
{
	long	tstamp;

	tstamp = ft_time() - sack->start_time;
	pthread_mutex_lock(&sack->printer);
	printf("(%ld ms) philosopher %d %s\n", tstamp, id + 1, action);
	pthread_mutex_unlock(&sack->printer);
}
