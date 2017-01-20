/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:02:02 by tsanzey           #+#    #+#             */
/*   Updated: 2016/12/29 17:02:04 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include "op.h"
#include <stdio.h>

int		index_array(char const *array[], char *str, int length)
{
	int i;

	i = 0;
	while (i < length)
	{
		if (ft_strcmp(array[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		line_type(char *str)
{
	if (label_index(str) > -1)
		return (LABELS);
	if (ft_strstr(str, ".name") == str)
		return (NAME);
	if (ft_strstr(str, ".comment") == str)
		return (COMMENT);
	return (OP);
}
