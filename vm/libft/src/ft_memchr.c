/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 01:21:51 by ybeaure           #+#    #+#             */
/*   Updated: 2015/11/27 20:42:10 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str1;
	unsigned int	i;

	i = 0;
	str1 = (unsigned char *)s;
	while (n--)
	{
		if ((unsigned char)c == str1[i])
			return (str1 + i);
		i++;
	}
	return (NULL);
}
