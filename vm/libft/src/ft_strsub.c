/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 04:52:36 by ybeaure           #+#    #+#             */
/*   Updated: 2015/11/30 07:51:38 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;

	if (s)
	{
		i = 0;
		if (start > ft_strlen(s))
			return (NULL);
		ret = (char *)malloc(sizeof(char) * len + 1);
		if (!ret)
			return (NULL);
		while (i < len && s[start])
		{
			ret[i] = s[start];
			i++;
			start++;
		}
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}
