/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:57:59 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/08 13:04:00 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_printer(t_sack *sack, long tstamp, int id, char *action)
{
	pthread_mutex_lock(&sack->printer);
	printf("%ld %d %s\n", tstamp, id + 1, action);
	pthread_mutex_unlock(&sack->printer);
}