/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:17:00 by sacorder          #+#    #+#             */
/*   Updated: 2023/09/27 12:17:12 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include "philo_structs.h"
# include "defines.h"

//utils.c

int		ft_error_exit(char *str, int n);
int		ft_space_or_digit(char c);
int		ft_atoi(char *str);
void	ft_printer(t_sack *sack, int id, char *action);
void	ft_print_dead(t_sack *sack, int id);

//utils2.c

long	ft_time(void);
void	ft_sleep(long t);
long	millis_since(long t);
void	killall(t_sack *sack);
int		check_str_posint(char *str);

//philos.c

void	*philos_routine(void *arg);
void	set_state(t_philo *philo, int val);
void	set_last_meal(t_philo *philo);
void	inc_meal_ctr(t_philo *philo);

//controller.c

void	checker(t_sack *sack);
int		init(t_sack *s);
int		start(t_sack *sack);

//philo_utils.c

int		get_state(t_philo *philo);
long	get_last_meal(t_philo *philo);
int		get_meal_ctr(t_philo *philo);
char	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);

#endif
