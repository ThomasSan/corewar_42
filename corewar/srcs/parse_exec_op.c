/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:11:24 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/12 16:29:14 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op		g_op_tab[17];

static int	not_op(char p_code[4], char opcode)
{
	int		i;

	i = 0;
	while (i < g_op_tab[opcode - 1].nb_arg)
	{
		if (p_code[i])
			return (get_p_len(p_code[i], opcode));
		i++;
	}
	return (0);
}



void		parse_exec_op(t_vm *vm, t_process *pro)
{
	char	p_code[4];
	int		p_val[4];
	int		next_op_pos;
	int		prev_op_pos;

	next_op_pos = get_p_nfo(vm, pro, p_code, p_val);
	prev_op_pos = pro->pc;
	if (check_params(pro->curr_op, p_code, p_val))
	{
		(g_exec_op[pro->curr_op - 1])(vm, pro, p_code, p_val);
		if (pro->curr_op != 9 || !pro->carry)
			pro->pc += next_op_pos;
	}
//	else
//{

//				display_debug_ram(vm->ram, vm->cycle.cycles);
//		pro->pc += not_op(p_code, pro->curr_op) + 2;
//exit(-1);
//}
	pro->curr_op = vm->ram[pro->pc % MEM_SIZE].value < 17 && (vm->ram[pro->pc
			% MEM_SIZE].value) ? vm->ram[pro->pc].value : 0;
	pro->cycles_to_exec = vm->ram[pro->pc % MEM_SIZE].value < 17 &&
		(vm->ram[pro->pc % MEM_SIZE].value) ?
		g_op_tab[pro->curr_op - 1].nb_cycle - 1 : 0;
	vm->ram[prev_op_pos % MEM_SIZE].executed = 0;
	vm->ram[pro->pc].executed = 1;
}
