/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_hexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:02:08 by tsanzey           #+#    #+#             */
/*   Updated: 2016/12/29 17:02:09 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include <stdio.h>

int		length_in_base(int nb, int base)
{
	int	i;

	i = 0;
	if (nb < 0)
		nb = -nb;
	while (nb > 0)
	{
		nb /= base;
		i++;
	}
	return (i);
}

char	*str_itobase(int nb, int base)
{
	const char	*symbols = "0123456789abcdef";
	char		*str;
	char		*tmp;
	int			len;

	len = length_in_base(nb, base);
	str = (char*)malloc(sizeof(char) * len + 1);
	str[len] = '\0';
	len--;
	if (nb == 0)
		return (ft_strdup("00"));
	while (nb > 0)
	{
		str[len] = symbols[nb % base];
		nb /= base;
		len--;
	}
	if (ft_strlen(str) == 1)
	{
		tmp = str;
		str = ft_strjoin("0", str);
		free(tmp);
	}
	return (str);
}

char	*fillnumbers(char *bin)
{
	int		i;
	int		len;
	char	*tmp;
	char	*dst;

	if (!(dst = (char*)malloc(sizeof(char) * 9)))
		return (NULL);
	i = 0;
	len = 8 - ft_strlen(bin);
	while (i < len)
	{
		dst[i] = '0';
		i++;
	}
	dst[i] = '\0';
	tmp = dst;
	dst = ft_strjoin(dst, bin);
	free(tmp);
	free(bin);
	return (dst);
}

char	*negative(char *bin)
{
	int i;

	i = 0;
	while (bin[i])
	{
		bin[i] = bin[i] == '0' ? '1' : '0';
		i++;
	}
	return (bin);
}

int		binary_todec(char *bin)
{
	int	i;
	int	mult;
	int nb;

	i = 7;
	mult = 1;
	nb = 0;
	while (i >= 0)
	{
		nb += (bin[i] - '0') * mult;
		mult *= 2;
		i--;
	}
	return (nb);
}
