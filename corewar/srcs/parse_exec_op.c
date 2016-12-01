/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:11:24 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/01 17:40:41 by ybeaure          ###   ########.fr       */
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

	pro->pc = 0;
	next_op_pos = get_p_nfo(vm, pro, p_code, p_val);
	prev_op_pos = pro->pc;
	dprintf(2, "%#X\n", pro->curr_op);
	if (check_params(pro->curr_op, p_code, p_val))
	{
		dprintf(2, "%#X\n", pro->curr_op + 1);
		ft_putendl_fd("YOLO", 2);
		(exec_op[pro->curr_op])(vm, pro, p_code, p_val);
		ft_putendl_fd("YOLO2", 2);
		if (pro->curr_op != 9 || pro->carry)
			pro->pc += next_op_pos;
	}
	pro->pc = (pro->pc + MEM_SIZE) % MEM_SIZE;
	pro->curr_op = vm->ram[pro->pc % MEM_SIZE].value < 17 && (vm->ram[pro->pc % MEM_SIZE].value) ? vm->ram[pro->pc].value : 0;
	dprintf(2, "%#X\n", pro->pc);
	vm->ram[prev_op_pos % MEM_SIZE].executed = 0;
	vm->ram[pro->pc].executed = 1;
}
