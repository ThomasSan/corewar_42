/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 13:07:36 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/15 13:11:28 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_pro	*find_dead_pro(t_pro **pro)
{
	t_pro	*tmp;

	if (pro && *pro)
	{
		tmp = *pro;
		while (tmp)
		{
			if (tmp->lives == 0)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

void		kill_pro(t_pro *pro, t_vm *vm)
{
	t_pro	*tmp;
	t_pro	*back;
	t_pro	*first;

	tmp = *(pro->start);
	first = tmp;
	back = 0;
	while (tmp)
	{
		if (tmp == pro)
		{
			if (back)
				back->next = tmp->next;
			else
				*(pro->start) = tmp->next;
			vm->ram[tmp->pc].execute = 0;
			free(tmp);
			tmp = NULL;
			return ;
		}
		back = tmp;
		tmp = tmp->next;
	}
}
