#include "../inc/philosophers.h"
#include <unistd.h>

void	ft_error_exit(char *str, int n)
{
	while (*str)
		write(2, (str++), 1);
	exit(n);
}
