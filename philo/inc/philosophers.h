/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:00 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/11 17:53:31 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include "philo_structs.h"
# include "defines.h"

//utils.c

int		ft_error_exit(char *str, int n);
int		ft_space_or_digit(char c);
int		ft_atoi(char *str);
void	ft_printer(t_sack *sack, int id, char *action);
void	ft_print_dead(t_sack *sack, int id, char *action);

//time.c

long	ft_time(void);
void	ft_sleep(long t);
long	millis_since(long t);

//philos.c

int		init(t_sack *s);

//checker.c

int		checker(t_sack *sack);

#endif
