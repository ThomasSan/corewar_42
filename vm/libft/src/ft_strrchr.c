/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:27:57 by ybeaure           #+#    #+#             */
/*   Updated: 2016/05/21 18:12:13 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char		*ft_strrchr(const char *s, int c)
{
	int		i;
	char	b;

	b = c;
	i = ft_strlen((char*)s);
	if (!s)
		return (NULL);
	while (s[i] != b && i > 0)
		--i;
	if (s[i] == b)
		return ((char*)s + i);
	return (NULL);
}
