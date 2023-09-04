#include "../inc/philosophers.h"
#include <unistd.h>

void	ft_error_exit(char *str, int n)
{
	while (*str)
		write(2, (str++), 1);
	exit(n);
}

int	ft_space_or_digit(char c)
{
	if ((c >= '0' && c <= '9') || c == ' '
		|| c == '\v' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\r') && str[i])
		++i;
	while(str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		++i;
	}
	return (res);
}
