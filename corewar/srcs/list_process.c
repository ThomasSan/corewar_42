/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:06:44 by cchameyr          #+#    #+#             */
/*   Updated: 2016/12/07 16:04:43 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op			op_tab[17];

static t_process	*new_process(int pc, int curr_op, t_process *parent)
{
	t_process	*pro;

	pro = (t_process *)ft_memalloc(sizeof(t_process));
	pro->pc = pc;
	pro->next = NULL;
	pro->lives = 0;
	if (parent)
	{
		pro->carry = parent->carry;
//		parent->reg[5] = 0xDD;
		ft_memcpy(pro->reg, parent->reg, REG_NUMBER);
//		ft_printf("last reg : %#x\nnew reg : %#x\n", parent->reg[5], pro->reg[5]);
//		exit(1);
//		debug a faire ici :D
	}
	else
		pro->carry = CARRY_ON_START;
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
//	static int		lol = 0;
//	ft_printf("MALLOC %d\n", lol++);
	return (pro);
}

void				add_process(t_process **p, int pc, int c_op, t_process *par)
{
	t_process		*pro;

	if (*p == NULL)
		*p = new_process(pc, c_op, par);
	else
	{
		pro = *p;
		while (pro->next)
			pro = pro->next;
		pro->next = new_process(pc, c_op, par);
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
