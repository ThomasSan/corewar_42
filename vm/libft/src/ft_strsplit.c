/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 05:22:39 by ybeaure           #+#    #+#             */
/*   Updated: 2015/11/30 05:29:05 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strsplit(const char *s, char c)
{
	size_t	i;
	size_t	j;
	int		beg;
	int		end;
	char	**tab;

	tab = NULL;
	i = 0;
	j = 0;
	if (s && (tab = (char **)malloc(sizeof(*tab) * (ft_strlen(s) / 2 + 2))))
	{
		while (s[i])
		{
			while (s[i] && s[i] == c)
				i++;
			beg = i;
			while (s[i] && s[i] != c)
				i++;
			end = i;
			if (end > beg)
				tab[j++] = ft_strsub(s, beg, (end - beg));
		}
		tab[j] = NULL;
	}
	return (tab);
}
