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

void	display_document(t_champ *head)
{
	while (head)
	{
		ft_putstr("head ");
		ft_putstr(head->line);
		ft_putstr(" -> ");
		ft_putnbr(head->type);
		ft_putstr(" @ ");
		ft_putnbr(head->address);
		if (head->type == OP || head->type == REG ||
			head->type == DIR || head->type == IND)
		{
			ft_putstr(" # ");
			ft_putnbr(head->value);
		}
		else
			ft_putchar('\n');
		head = head->next;
	}
}

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
