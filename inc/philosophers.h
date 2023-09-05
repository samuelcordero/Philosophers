/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:00 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/05 20:17:01 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include "philo_structs.h"

//utils.c

void	ft_error_exit(char *str, int n);
int		ft_space_or_digit(char c);
int		ft_atoi(char *str);

//time.c

long	ft_time(void);
void	ft_sleep(long t);
long	millis_since(long t);

#endif
