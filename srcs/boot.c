/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 15:21:54 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 16:39:06 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	init_nbr_cycle_op(int nbr_cycle[16])
{
	nbr_cycle[0] = 10;
	nbr_cycle[1] = 5;
	nbr_cycle[2] = 5;
	nbr_cycle[3] = 10;
	nbr_cycle[4] = 10;
	nbr_cycle[5] = 6;
	nbr_cycle[6] = 6;
	nbr_cycle[7] = 6;
	nbr_cycle[8] = 20;
	nbr_cycle[9] = 25;
	nbr_cycle[10] = 25;
	nbr_cycle[11] = 800;
	nbr_cycle[12] = 10;
	nbr_cycle[13] = 50;
	nbr_cycle[14] = 1000;
	nbr_cycle[15] = 2;
}

void	init_argc_op(int argc[16])
{
	argc[0] = 1;
	argc[1] = 2;
	argc[2] = 2;
	argc[3] = 3;
	argc[4] = 3;
	argc[5] = 3;
	argc[6] = 3;
	argc[7] = 3;
	argc[8] = 1;
	argc[9] = 3;
	argc[10] = 3;
	argc[11] = 1;
	argc[12] = 2;
	argc[13] = 3;
	argc[14] = 1;
	argc[15] = 1;
}

void	init_size_arg_op(int size_arg[16])
{
	size_arg[0] = 4;
	size_arg[1] = 4;
	size_arg[2] = 04;
	size_arg[3] = 04;
	size_arg[4] = 04;
	size_arg[5] = 4;
	size_arg[6] = 4;
	size_arg[7] = 4;
	size_arg[8] = 2;
	size_arg[9] = 2;
	size_arg[10] = 2;
	size_arg[11] = 2;
	size_arg[12] = 4;
	size_arg[13] = 2;
	size_arg[14] = 2;
	size_arg[15] = 04;
}

void	init_op(t_vm *vm)
{
	vm->op_function[0] = op_live;
	vm->op_function[1] = op_ld;
	vm->op_function[2] = op_st;
	vm->op_function[3] = op_add;
	vm->op_function[4] = op_sub;
	vm->op_function[5] = op_and;
	vm->op_function[6] = op_or;
	vm->op_function[7] = op_xor;
	vm->op_function[8] = op_zjmp;
	vm->op_function[9] = op_ldi;
	vm->op_function[10] = op_sti;
	vm->op_function[11] = op_fork;
	vm->op_function[12] = op_lld;
	vm->op_function[13] = op_lldi;
	vm->op_function[14] = op_lfork;
	vm->op_function[15] = op_aff;
}

t_vm	*boot_vm(void)
{
	t_vm		*vm;
	int			i;

	vm = ft_memalloc(sizeof(t_vm));
	vm->cycle_to_exec = -1;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->print_live = 1;
	init_nbr_cycle_op(vm->nbr_cycle);
	init_argc_op(vm->argc);
	init_size_arg_op(vm->size_arg);
	init_op(vm);
	i = -1;
	while (++i < MAX_PLAYERS)
		vm->champ[i].dead = 1;
	return (vm);
}
