/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:06:44 by cchameyr          #+#    #+#             */
/*   Updated: 2016/11/30 15:14:08 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static t_process	*new_process(int pc, int curr_op, int carry)
{
	t_process	*pro;

	pro = (t_process *)ft_memalloc(sizeof(t_process));
	pro->pc = pc;
	pro->curr_op = curr_op;
	pro->carry = carry;
	pro->next = NULL;
	return (pro);
}

void				add_process(t_process **p, int pc, int curr_op, int carry)
{
	t_process		*pro;

	if (*p == NULL)
		*p = new_process(pc, curr_op, carry);
	else
	{
		pro = *p;
		while (pro->next)
			pro = pro->next;
		pro->next = new_process(pc, curr_op, carry);
	}
}
