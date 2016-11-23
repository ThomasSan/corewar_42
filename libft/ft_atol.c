#include "push_swap.h"

long		ft_atol(char *str)
{
	int		sign;
	long	val;
	long	nb;

	sign = 1;
	nb = 0;
	val = 0;
	while (*str == ' ' || *str == '\n' || *str == '\v' || *str == '\r'
			|| *str == '\t' || *str == '\f')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = *str - '0';
		val = (val * 10) + nb;
		str++;
	}
	return (val * sign);
}
