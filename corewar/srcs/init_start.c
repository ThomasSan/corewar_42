/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:19:35 by cchameyr          #+#    #+#             */
/*   Updated: 2016/12/14 13:41:32 by cchameyr         ###   ########.fr       */
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

static void		init_reg(t_vm *vm)
{
	t_process		*pro;
	int				c;
	int				i;

	pro = vm->process;
	c = -1;
	while (pro)
	{
		i = 0;
		pro->reg[i] = vm->champs[++c].n_code;
		while (++i < REG_NUMBER)
			pro->reg[i] = 0;
		pro = pro->next;
	}
}

static void		init_process(t_vm *vm)
{
	int			c;

	c = -1;
	while (++c < vm->nb_champ)
	{
		add_process(&vm->process, vm->champs[c].pos,
				vm->ram[vm->champs[c].pos].value, NULL);
		vm->ram[vm->champs[c].pos].executed = 1;
	}
	init_reg(vm);
}

static void		init_cycles(t_vm *vm)
{
	vm->cycle.cycles = 0;
	vm->cycle.cycle_delta = CYCLE_DELTA;
	vm->cycle.nbr_live = NBR_LIVE;
	vm->cycle.checks_done = 0;
	vm->cycle.cycle_to_die = CYCLE_TO_DIE;
	vm->cycle.cycles_before_die = 0;
	vm->last_to_live = vm->nb_champ - 1;
}

void			init_start(t_vm *vm)
{
	place_champ(vm);
	init_process(vm);
	init_cycles(vm);
}
