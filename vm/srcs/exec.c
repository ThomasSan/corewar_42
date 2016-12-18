/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 13:20:45 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 18:17:48 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op	g_op_tab[17];

static int	not_op(char p_code[4], char opcode)
{
	int		i;

	i = 0;
	while (i < g_op_tab[opcode - 1].nbr_param)
	{
		if (p_code[i])
			return (get_p_len(p_code[i], opcode));
		i++;
	}
	return (0);
}

void		exec_op(t_pro *pro, t_vm *vm)
{
	char	p_code[4];
	int		p_val[4];
	int		next_position;
	int		old_position;

	next_position = get_p_info(pro, vm, p_code, p_val);
	old_position = pro->pc;
	if (check_params(pro->curr_op, p_code, p_val))
	{
		(*g_exec_op[pro->curr_op - 1])(vm, pro, p_code, p_val);
		if (pro->curr_op != 9 || !pro->carry)
			pro->pc += next_position;
	}
	else
		pro->pc += not_op(p_code, pro->curr_op) + 2;
	pro->pc = (pro->pc + MEM_SIZE) % MEM_SIZE;
	pro->curr_op = vm->ram[pro->pc % MEM_SIZE].value < 17 && (vm->ram[pro->pc % MEM_SIZE].value) ? vm->ram[pro->pc].value : 0;
	pro->cycles_to_exec = vm->ram[pro->pc % MEM_SIZE].value < 17 && (vm->ram[pro->pc % MEM_SIZE].value) ? g_op_tab[pro->curr_op - 1].nbr_cycles - 1 : 0;
	vm->ram[old_position % MEM_SIZE].execute = 0;
	vm->ram[pro->pc].execute = 1;
}

void		try_exec(t_pro *pro, t_vm *vm)
{
	if (pro->curr_op)
	{
		if (pro->cycles_to_exec <= 0)
			exec_op(pro, vm);
		else
			pro->cycles_to_exec--;
	}
	else
	{
		vm->ram[pro->pc].execute = 0;
		pro->pc = (pro->pc + 1) % MEM_SIZE;
		vm->ram[pro->pc].execute = 1;
		if (vm->ram[pro->pc % MEM_SIZE].value && vm->ram[pro->pc % MEM_SIZE].value < 17)
		{
			pro->curr_op = vm->ram[pro->pc % MEM_SIZE].value;
			pro->cycles_to_exec = g_op_tab[pro->curr_op - 1].nbr_cycles - 1;
		}
	}
}

void		exec_pro(t_pro **pro, t_vm *vm)
{
	t_pro *tmp;

	if (pro && *pro)
	{
		tmp = *pro;
		while (tmp)
		{
			try_exec(tmp, vm);
			tmp = tmp->next;
		}
	}
}
