/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_tables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:04:34 by tsanzey           #+#    #+#             */
/*   Updated: 2016/12/29 17:04:35 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include "op.h"
#include <stdio.h>

int		label_sizes(char *str)
{
	const char	*size_of_two[] = {"zjmp", "ldi", "sti", "fork",
	"lldi", "lfork"};
	const char	*size_of_four[] = {"live", "ld", "and", "or", "xor", "lld"};

	if (index_array(size_of_two, str, 6) > -1)
		return (2);
	if (index_array(size_of_four, str, 6) > -1)
		return (4);
	return (-1);
}

int		params_types(char *str)
{
	const char *no_encoding[] = {"live", "zjmp", "fork", "lfork"};

	if (index_array(no_encoding, str, 4) > -1)
		return (1);
	return (2);
}

int		get_op_code(char *str)
{
	const char	*op[] = {"live", "ld", "st", "add", "sub", "and", "or", "xor",
	"zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"};
	int			index;

	index = index_array(op, str, 16);
	free(str);
	if (index > -1)
		return (index);
	return (-1);
}

int		string_is_number(char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (1);
}

int		get_param_type(char *tmp)
{
	char	*str;
	int		ret;

	ret = -1;
	str = ft_strtrim(tmp);
	free(tmp);
	if (str[0] == 'r')
	{
		if (string_is_number(str))
			ret = REG;
	}
	else if (str[0] == '%')
	{
		if (str[1] == ':' || string_is_number(str))
			ret = DIR;
	}
	else
	{
		if (str[0] == ':' || string_is_number(str))
			ret = IND;
	}
	free(str);
	return (ret);
}
