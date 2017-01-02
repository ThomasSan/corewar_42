/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 17:32:07 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 17:33:04 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

long long int	ft_atol(const char *str)
{
	long long int	result;
	int				sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
			*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = (*str - '0') + result * 10;
		str++;
	}
	return (result * (long long int)sign);
}

int				ft_isint(char *s_int, int *result)
{
	int				i;
	int				r;
	long long int	tmp;

	i = 0;
	if (s_int[0] == 0)
		return (0);
	while (s_int[i])
	{
		if (!ft_isdigit(s_int[i]) &&
				!(s_int[i] == '-' && i == 0 && s_int[1]))
			return (0);
		i++;
	}
	tmp = ft_atol(s_int);
	r = (int)tmp;
	if ((long long int)r != tmp)
		return (0);
	*result = r;
	return (1);
}

t_lst			*ft_lstnew_noalloc(void *data, size_t data_size)
{
	t_lst *result;

	result = (t_lst*)ft_memalloc(sizeof(t_lst));
	if (result == NULL)
		return (NULL);
	result->next = NULL;
	if (data == NULL)
	{
		result->data = NULL;
		result->data_size = 0;
		return (result);
	}
	result->data_size = data_size;
	result->data = data;
	if (result->data == NULL)
	{
		result->data_size = 0;
		return (NULL);
	}
	return (result);
}
