/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_battle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 14:49:13 by cchameyr          #+#    #+#             */
/*   Updated: 2016/12/09 13:12:14 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op		op_tab[17];

static void		exec_process(t_vm *vm, t_process *pro)
{
	if (pro->curr_op)
	{
		if (pro->cycles_to_exec <= 0)
			parse_exec_op(vm, pro);
		else
			pro->cycles_to_exec--;
	}
	else
	{
		vm->ram[pro->pc].executed = 0;
		pro->pc = (pro->pc + 1) % MEM_SIZE;
		vm->ram[pro->pc].executed = 1;
		if (vm->ram[pro->pc % MEM_SIZE].value <= 16 &&
				vm->ram[pro->pc % MEM_SIZE].value > 0)
		{
			pro->curr_op = vm->ram[pro->pc % MEM_SIZE].value;
			pro->cycles_to_exec = op_tab[pro->curr_op - 1].nb_cycle - 1;
		}
	}
}

static void		update_cycle_and_lives(t_cycle *cycle, t_process *pro)
{
	int		total_lives;

	total_lives = 0;
	while (pro)
	{
		total_lives += pro->lives;
		pro->lives = 0;
		pro = pro->next;
	}
	if (total_lives >= NBR_LIVE || cycle->checks_done >= MAX_CHECKS)
	{
		cycle->cycle_to_die -= CYCLE_DELTA;
		cycle->checks_done = 0;
	}
	else
		cycle->checks_done++;
}

static int		update_cycle(t_vm *vm, t_cycle *cycle)
{
	t_process	*dead_pro;

	cycle->cycles++;
	if (cycle->cycles_before_die == cycle->cycle_to_die)
	{
		while ((dead_pro = get_dead_process(vm->process)))
			remove_dead_process(dead_pro, vm);
		if (!vm->process)
			return (0);
		cycle->cycles_before_die = 0;
		update_cycle_and_lives(cycle, vm->process);
		if (cycle->cycle_to_die <= 0)
			return (0);
		return (1);
	}
	else
	{
		cycle->cycles_before_die++;
		return (1);
	}
}

void			start_battle(t_vm *vm)
{
	int			game;
	t_process	*pro;
	int			i = 0;

	game = 1;
	while (game)
	{
		pro = vm->process;
		while (pro)
		{
			exec_process(vm, pro);
			pro = pro->next;
		}
		game = update_cycle(vm, &vm->cycle);
	//	display_debug_ram(vm->ram, vm->cycle.cycles);
//		usleep(21000);
//		ft_printf("%d\n", vm->cycle.cycles);
	if (i++ == 100)
	{
		display_debug_ram(vm->ram, vm->cycle.cycles);
		i = 0;
	}
	}
	//display_debug_ram(vm->ram, vm->cycle.cycles);
	ft_printf("gagnant : %s\n", vm->champs[vm->last_to_live].header.prog_name);
}
