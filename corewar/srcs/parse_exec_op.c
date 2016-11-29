/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:11:24 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/29 20:37:38 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op		op_tab[17];

void		parse_exec_op(t_vm *vm, t_process *pro)
{
	char	p_code[4];
	int		p_val[4];
	int		next_op_pos;
	int		prev_op_pos;

	pro->pc = 2048;
	next_op_pos = get_p_nfo(vm, pro, p_code, p_val);
	prev_op_pos = pro->pc;
	if (check_params(pro->curr_op, p_code, p_val))
	{
		(exec_op[pro->curr_op - 1])(vm, pro, p_code, p_val);
		if (pro->curr_op != 9 || pro->carry)
			pro->pc = pro->pc + next_op_pos;
	}
	pro->pc = (pro->pc + MEM_SIZE) % MEM_SIZE;
	pro->curr_op = vm->ram[pro->pc % MEM_SIZE].value <= 16 && (vm->ram[pro->pc % MEM_SIZE].value) ? vm->ram[pro->pc].value : 0;
//	vm->ram[prev_op_pos % MEM_SIZE].exec = 0;
//	vm->ram[pro->pc].exec = 1;
}
