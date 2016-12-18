/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 15:20:52 by ybeaure           #+#    #+#             */
/*   Updated: 2015/11/29 21:35:48 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*ret;
	int		len;
	int		is_neg;
	int		tmp;

	len = n < 0 ? 1 : 0;
	is_neg = len;
	n = n < 0 ? -n : n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if ((tmp = n) == 0 || n == -0)
		return (ft_strdup("0"));
	while (n && ++len)
		n = n / 10;
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[len] = '\0';
	while (tmp && len--)
	{
		ret[len] = (tmp % 10) + '0';
		tmp = tmp / 10;
	}
	if (is_neg)
		ret[0] = '-';
	return (ret);
}
