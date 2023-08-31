#include "../inc/philosophers.h"

static void	check_args(int argc, char **argv)
{
	(void)argv;
	if (argc < 5 || argc > 6)
		ft_error_exit("Invalid number of args", 1);
}

int	main(int argc, char **argv)
{
	check_args(argc, argv);
	printf("testing\n");
	return (0);
}
