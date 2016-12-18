/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 05:25:59 by ybeaure           #+#    #+#             */
/*   Updated: 2015/11/30 07:45:59 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
			ret[i] = f(str[i]);
			i++;
		}
		ret[i] = 0;
		return (ret);
	}
	return (NULL);
}
