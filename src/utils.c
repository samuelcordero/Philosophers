#include "../inc/philosophers.h"

void	ft_error_exit(char *str, int n)
{
	ft_putendl_fd(str, 2);
	exit(n);
}
