/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:18:00 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/15 12:32:08 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op		g_op_tab[17];

void			init_register(int reg[REG_NUMBER], int champ_nbr)
{
	int		i;
	
	i = 0;
	reg[0] = champ_nbr;
	while (++i < REG_NUMBER)
		reg[i] = 0;
}

void			init_single_pro(t_pro *pro, t_vm *vm, int champ_nbr)
{
	pro->pc = vm->champs[champ_nbr].position;
	if (vm->ram[pro->pc % MEM_SIZE].value <= 16 && vm->ram[pro->pc % MEM_SIZE].value)
	{
		pro->curr_op = vm->ram[pro->pc % MEM_SIZE].value;
		pro->cycles_to_exec = g_op_tab[pro->curr_op - 1].nbr_cycles - 1;
	}
	else
	{
		pro->cycles_to_exec = 0;
		pro->curr_op = 0;
	}
	init_register(pro->reg, vm->champs[champ_nbr].number);
	pro->carry = 1;
	pro->lives = 0;
	pro->champ = vm->ram[pro->pc % MEM_SIZE].champ;
}

void			init_all_pro(t_pro **pro, t_vm *vm)
{
	int		i;
	t_pro	*tmp;

	i = vm->nbr_champs - 1;
	*pro = malloc(sizeof(t_pro));
	tmp = *pro;
	tmp->start = pro;
	init_single_pro(tmp, vm, i);
	while (--i >= 0)
	{
		tmp->next = malloc(sizeof(t_pro));
		init_single_pro(tmp->next, vm, i);
		tmp->next->start = pro;
		tmp = tmp->next;
	}
	tmp->next = NULL;
}

void			init_cycle(t_cycle *cycle, t_vm *vm)
{
	cycle->cycle_to_die = CYCLE_TO_DIE;
	cycle->cycles_done = 0;
	cycle->dump_cycle = vm->dump_cycle;
	cycle->pro = malloc(sizeof(t_pro*));
	cycle->checks_done = 0;
	vm->last_to_live = vm->nbr_champs - 1;
	cycle->pro_nbr = vm->nbr_champs;
	init_all_pro(cycle->pro, vm);
}
