/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 14:32:07 by tsanzey           #+#    #+#             */
/*   Updated: 2017/01/24 15:26:24 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "assembleur.h"
#include <stdio.h>

int			is_a_label_char(char c)
{
	int		i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (LABEL_CHARS[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int			check_ind(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == LABEL_CHAR)
			continue ;
		if (!is_a_label_char(str[i]))
			error_and_exit(ALL, str);
		i++;
	}
	return (0);
}

int			check_dir(char *str)
{
	int		i;
	int		ret;

	i = 1;
	ret = string_is_number(str);
	while (str[i])
	{
		if (i == 0 && str[i] == DIRECT_CHAR)
			i++;
		if (i == 1 && str[i] == LABEL_CHAR)
			i++;
		if (ret == -1 && !is_a_label_char(str[i]))
			error_and_exit(ALL, str);
		i++;
	}
	return (0);
}

int			check_reg(char *str)
{
	if (string_is_number(str) < 0)
		error_and_exit(ALL, str);
	return (0);
}

void		arg_validity(t_champ *head)
{
	while (head)
	{
		if (head->type == IND)
			check_ind(head->line);
		if (head->type == DIR)
			check_dir(head->line);
		if (head->type == REG)
			check_reg(head->line);
		head = head->next;
	}
}
