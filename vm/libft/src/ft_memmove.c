/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <ybeaure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 20:43:35 by ybeaure           #+#    #+#             */
/*   Updated: 2015/11/29 06:31:01 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*str1;
	char	*str2;

	str1 = (char *)src;
	str2 = (char *)dst;
	if (str1 < str2)
	{
		str1 = str1 + len - 1;
		str2 = str2 + len - 1;
		while (len)
		{
			*str2-- = *str1--;
			len--;
		}
	}
	while (len--)
		*str2++ = *str1++;
	return (dst);
}
