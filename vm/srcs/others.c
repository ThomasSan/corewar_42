/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 20:24:23 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/15 13:19:43 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

char	*ft_strrev(char *s)
{
	char	*rev;
	int		i;
	int		size;

	if (s == NULL)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	rev = (char *)malloc(sizeof(char) * size + 1);
	if (rev == NULL)
		return (NULL);
	size--;
	while (size != -1)
		rev[i++] = s[size--];
	rev[i] = '\0';
	return (rev);
}

int		array_size(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**ft_arrsub(char **src, unsigned int start, unsigned int len)
{
	char			**out;
	unsigned int	i;

	i = 0;
	if (src == NULL || i + len > (unsigned int)array_size(src))
		return (NULL);
	out = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len && src[start] != NULL)
		out[i++] = ft_strdup(src[start++]);
	out[i] = NULL;
	return (out);
}
