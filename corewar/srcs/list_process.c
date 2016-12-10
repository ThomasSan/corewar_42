/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:06:44 by cchameyr          #+#    #+#             */
/*   Updated: 2016/12/10 18:05:16 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op			g_op_tab[17];

static t_process	*new_process(int pc, int curr_op, t_process *parent, int i)
{
	t_process	*pro;

	pro = (t_process *)ft_memalloc(sizeof(t_process));
	pro->pc = pc;
	pro->next = NULL;
	pro->lives = 0;
	if (parent)
	{
		pro->carry = parent->carry;
		while (++i < REG_NUMBER)
			pro->reg[i] = parent->reg[i];
	}
	else
		pro->carry = CARRY_ON_START;
	if (curr_op <= 16 && curr_op > 0)
	{
		pro->curr_op = curr_op;
		pro->cycles_to_exec = g_op_tab[curr_op - 1].nb_cycle;
	}
	else
	{
		pro->curr_op = 0;
		pro->cycles_to_exec = 0;
	}
	return (pro);
}

void				add_process(t_process **p, int pc, int c_op, t_process *par)
{
	t_process		*pro;

	if (*p == NULL)
		*p = new_process(pc, c_op, par, -1);
	else
	{
		pro = *p;
		while (pro->next)
			pro = pro->next;
		pro->next = new_process(pc, c_op, par, -1);
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

t_process			*get_dead_process(t_process *pro)
{
	while (pro)
	{
		if (pro->lives == 0)
			return (pro);
		pro = pro->next;
	}
	return (NULL);
}

void				remove_dead_process(t_process *dead_pro, t_vm *vm)
{
	t_process	*pro;
	t_process	*last;
	t_process	*first;

	pro = vm->process;
	first = pro;
	last = NULL;
	while (pro)
	{
		if (pro == dead_pro)
		{
			if (last)
				last->next = pro->next;
			else
				vm->process = pro->next;
			vm->ram[pro->pc].executed = 0;
			ft_memdel((void **)&pro);
			return ;
		}
		last = pro;
		pro = pro->next;
	}
}
