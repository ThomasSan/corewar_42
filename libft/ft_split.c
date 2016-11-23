/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:46:34 by tsanzey           #+#    #+#             */
/*   Updated: 2015/11/30 17:41:38 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int		count_word(const char *s)
{
	int i;
	int wd;

	i = 0;
	wd = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		wd++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (wd);
}

static int		word_len(char const *s, int start)
{
	int i;

	i = 0;
	while (s[start] && !ft_isspace(s[start]))
	{
		start++;
		i++;
	}
	return (i);
}

char			**ft_split(char const *s)
{
	char	**tab;
	int		word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word = count_word(s);
	if (!(tab = (char **)malloc(sizeof(char*) * (word + 1))))
		return (NULL);
	while (i < word)
	{
		while (s[j] && ft_isspace(s[j]))
			j++;
		tab[i] = ft_strsub(s, j, word_len(s, j));
		i++;
		while (s[j] && !ft_isspace(s[j]))
			j++;
	}
	tab[i] = NULL;
	return (tab);
}
