/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 23:02:59 by ybeaure           #+#    #+#             */
/*   Updated: 2015/11/28 22:36:08 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = -1;
	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	while (++i < n)
	{
		str1[i] = str2[i];
		if ((unsigned char)c == str2[i])
			return (str1 + i + 1);
	}
	return (NULL);
}
