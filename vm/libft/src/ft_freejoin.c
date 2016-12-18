/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freejoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 16:16:37 by ybeaure           #+#    #+#             */
/*   Updated: 2016/03/30 23:19:35 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_freejoin(char *s1, char *s2)
{
	char	*tmp;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (s1)
		ft_memdel((void**)&s1);
	if (s1)
		ft_memdel((void**)&s2);
	return (tmp);
}
