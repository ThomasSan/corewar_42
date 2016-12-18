/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:35:12 by ybeaure           #+#    #+#             */
/*   Updated: 2015/11/26 16:01:22 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*dst;

	dst = s1;
	while (*dst != '\0')
		dst++;
	ft_strncpy(dst, s2, n);
	return (s1);
}
