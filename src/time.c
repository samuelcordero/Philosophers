/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:19 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/05 20:17:20 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <bits/types/struct_timeval.h>
#include <sys/time.h>

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
		usleep(50);
}

