#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include "philo_structs.h"

void	ft_error_exit(char *str, int n);
int		ft_space_or_digit(char c);
int		ft_atoi(char *str);

#endif
