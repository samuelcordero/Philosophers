/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:57:59 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/08 13:41:11 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_printer(t_sack *sack, int id, char *action)
{
	long	tstamp;

	tstamp = ft_time() - sack->start_time;
	pthread_mutex_lock(&sack->printer);
	printf("%ld %d %s\n", tstamp, id + 1, action);
	pthread_mutex_unlock(&sack->printer);
}