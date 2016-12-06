/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:06:44 by cchameyr          #+#    #+#             */
/*   Updated: 2016/12/06 14:21:13 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op			op_tab[17];

static t_process	*new_process(int pc, int curr_op, int carry)
{
	t_process	*pro;

	pro = (t_process *)ft_memalloc(sizeof(t_process));
	pro->pc = pc;
	pro->next = NULL;
	pro->lives = 0;
	if (curr_op <= 16 && curr_op > 0)
	{
		pro->curr_op = curr_op;
		pro->cycles_to_exec = op_tab[curr_op - 1].nb_cycle;
	}
	else
	{
		pro->curr_op = 0;
		pro->cycles_to_exec = 0;
	}
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

void				free_process(t_process **p)
{
	t_process		*tmp;

	if (*p == NULL)
		return ;
	tmp = *p;
	while (tmp)
	{
		*p = tmp->next;
		ft_memdel((void **)&tmp);
		tmp = *p;
	}
	*p = NULL;
}
