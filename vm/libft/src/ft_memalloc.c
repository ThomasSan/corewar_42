/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 01:44:31 by ybeaure           #+#    #+#             */
/*   Updated: 2015/11/29 06:30:38 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *str;

	if (size)
		str = (char *)malloc(sizeof(char) * size);
	if (!size || !str)
		return (NULL);
	while (size--)
		str[size] = 0;
	return (str);
}
