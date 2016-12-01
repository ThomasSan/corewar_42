/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:26:30 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/01 19:11:42 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op		op_tab[17];

int		get_new_p_val(t_vm *vm, t_process *pro, char p_code, int p_val)
{
	int		ret;
	int		i;

	if (p_code == REG_CODE && p_val <= REG_NUMBER)
		return (vm->champs[vm->ram[pro->pc].owner].reg[p_val - 1]);
	else if (p_code == IND_CODE || (p_code == DIR_CODE && op_tab[vm->ram[pro->pc % MEM_SIZE].value].is_idx > 0))
	{
		ret = 0;
		i = 0;
		while (i != 3)
		{
			ret = ret << 8;
			ret = ret + vm->ram[(pro->pc + ((signed short)p_val % IDX_MOD) + i + MEM_SIZE) % MEM_SIZE].value;
			i++;
		}
		return (ret);
	}
	else
		return (p_val);
}

int		check_params(char opcode, char p_code[4], int p_val[4])
{
	int		i;

	opcode--;
	dprintf(2, "%s\n\n\n", op_tab[(int)opcode].comment);
	i = -1;
	if (opcode > 15)
		return (0);
	while (++i < op_tab[(int)opcode].nb_arg)
	{
		dprintf(2, "%s %#x\n","p_type[i] =", op_tab[(int)opcode].p_type[i]);
		dprintf(2, "%s %#x\n","p_code[i] =", p_code[i]);
		dprintf(2, "%s %#x\n","p_code[i] - 1 =", p_code[i] - 1);
		dprintf(2, "%s %#x\n","opcode] =", opcode);
		if ((op_tab[(int)opcode].p_type[i] >> (p_code[i] - 1)) % 2 == 0)
		{
		dprintf(2, "%s %#x\n", "final p_type[i] =", op_tab[(int)opcode].p_type[i]);
		dprintf(2, "%s %#x\n", "final p_code[i] =", p_code[i]);
			return (0);
		}
		if (p_code[i] == REG_CODE && p_val[i] > 16)
			return (0);
	}
	return (1);
}
