#include "../inc/philosophers.h"
#include <stdio.h>
#include <string.h>

static void	check_str_posint(char *str)
{
	while (*str)
	{
		if (!ft_space_or_digit(*str))
			ft_error_exit("Invalid args\n", 2);
		++str;
	}
}

static t_sack	*check_args(int argc, char **argv)
{
	int	i;
	t_sack *res;

	i = 0;
	if (argc < 5 || argc > 6)
		ft_error_exit("Invalid number of args\n", 1);
	while (argv[++i])
		check_str_posint(argv[i]);
	res = malloc(sizeof(t_sack));
	if (!res)
		ft_error_exit("Couldn't allocate mem\n", 1);
	memset(res, 0, sizeof(t_sack));
	res->nbr_philos = ft_atoi(argv[1]);
	res->time_to_die = ft_atoi(argv[2]);
	res->time_to_eat = ft_atoi(argv[3]);
	res->time_to_sleep = ft_atoi(argv[4]);
	res->meals = -1;
	if (argv[5])
		res->meals = ft_atoi(argv[5]);
	return (res);
}

int	main(int argc, char **argv)
{
	t_sack	*sack;
	long t;
	sack = check_args(argc, argv);
	printf("testing:\nphilos: %i\ntime2die %i\ntime2sleep %i\ntime2eat %i\ntotal meals %i\n", sack->nbr_philos, sack->time_to_die, sack->time_to_sleep, sack->time_to_eat, sack->meals);
	t = ft_time();
	printf("time: %ld\n", t);
	ft_sleep(2100);
	printf("time: %ld\n", millis_since(t));
	return (0);
}
