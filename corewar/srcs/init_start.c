/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:19:35 by cchameyr          #+#    #+#             */
/*   Updated: 2016/12/06 13:59:48 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void		place_champ(t_vm *vm)
{
	int		jump;
	int		c;
	int		i;

	jump = 0;
	c = -1;
	while (++c < vm->nb_champ)
	{
		i = -1;
		while (++i <= vm->champs[c].len)
		{
			vm->ram[jump + i].value = vm->champs[c].data[i];
			vm->ram[jump + i].owner = c;
			vm->champs[c].pos = jump;
		}
		jump += MEM_SIZE / vm->nb_champ;
	}
}

static void		init_process(t_vm *vm)
{
	int		jump;
	int		c;

	jump = (MEM_SIZE / vm->nb_champ) * (vm->nb_champ - 1);
	c = -1;
	while (++c < vm->nb_champ)
	{
		add_process(&vm->process, jump, vm->ram[jump].value, CARRY_ON_START);
		vm->ram[jump].executed = 1;
		jump -= MEM_SIZE / vm->nb_champ;
	}
}

static void		init_cycles(t_vm *vm)
{
	vm->cycle.cycles = 0;
	vm->cycle.cycle_delta = CYCLE_DELTA;
	vm->cycle.nbr_live = NBR_LIVE;
	vm->cycle.max_checks = MAX_CHECKS;
	vm->cycle.cycle_to_die = CYCLE_TO_DIE;
	vm->cycle.cycles_before_die = 0;
	vm->last_to_live = vm->nb_champ - 1;
}

static void		init_reg(t_vm *vm)
{
	int		c;
	int		i;

	c = -1;
	while (++c < vm->nb_champ)
	{
		i = 0;
		vm->champs[c].reg[0] = vm->champs[c].number + 9;
		while (++i < REG_NUMBER)
			vm->champs[c].reg[i] = 0;
	}
}

void			init_start(t_vm *vm)
{
	place_champ(vm);
	init_process(vm);
	init_cycles(vm);
	init_reg(vm);
}
