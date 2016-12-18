/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 05:27:00 by ybeaure           #+#    #+#             */
/*   Updated: 2015/11/30 09:07:42 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	char	*ret;
	size_t	i;

	str = (char *)s;
	i = 0;
	if (s && f)
	{
		if (!(ret = ft_memalloc(ft_strlen(str) + 1)))
			return (NULL);
		while (str[i])
		{
			ret[i] = (*f)(i, str[i]);
			i++;
		}
		ret[i] = 0;
		return (ret);
	}
	return (NULL);
}
