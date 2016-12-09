/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:26:30 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/09 18:23:59 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op		op_tab[17];

int		ft_loop_memory(int value)
{
	int		ret;

	ret = value;
		while (ret < 0)
			ret= MEM_SIZE + ret;
	if (ret >= MEM_SIZE)
		ret = value % MEM_SIZE;
	return (ret);
}

int		get_new_p_val(t_vm *vm, t_process *pro, char p_code, int p_val)
{
//	int		ret;
//	int		i;

//	dprintf(2, "pcode dans new_p_val=%#x\n", p_code);
//	if (p_code == REG_CODE && p_val <= REG_NUMBER)
//	{
//		return (pro->reg[p_val - 1]);
//		return (vm->champs[vm->ram[pro->pc].owner].reg[p_val - 1]);
//	}
//	else if (p_code == IND_CODE || (p_code == DIR_CODE &&
//				op_tab[vm->ram[pro->pc % MEM_SIZE].value].is_idx > 0))
//	{
//		ret = 0;
//		i = 0;
//		while (i != 3)
//		{
//			ret = ret << 8;
//			ret += vm->ram[(pro->pc + ((signed short)p_val % IDX_MOD) +
//					i + MEM_SIZE) % MEM_SIZE].value;
//			i++;
//		}
//		return (ret);
//	}
//	else
//		return (p_val);
	int ret;

	ret = 0;
	if (p_code == T_REG)
	   ret = pro->reg[p_val - 1];
	else if (p_code == IND_CODE)
		ret = vm->ram[ft_loop_memory(pro->pc + (p_val % IDX_MOD))].value;
	else if (p_code == T_DIR)
		ret = p_val;
//	pro->carry = 1;
	return (ret);
}

int		get_new_lp_val(t_vm *vm, t_process *pro, char p_code, int p_val)
{
	int		ret;
	int		i;

	if (p_code == REG_CODE && p_val <= REG_NUMBER)
		return (pro->reg[p_val - 1]);
	//	return (vm->champs[vm->ram[pro->pc].owner].reg[p_val - 1]);
	else if (p_code == IND_CODE || (p_code == DIR_CODE &&
				op_tab[vm->ram[pro->pc % MEM_SIZE].value].is_idx > 0))
	{
		ret = 0;
		i = 0;
		while (i != 3)
		{
			ret = ret << 8;
			ret += vm->ram[(pro->pc + (signed short)p_val +
					i + MEM_SIZE) % MEM_SIZE].value;
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
	i = -1;
	if (opcode > 15)
		return (0);
	while (++i < op_tab[(int)opcode].nb_arg)
	{
		if ((op_tab[(int)opcode].p_type[i] >> (p_code[i] - 1)) % 2 == 0)
			return (0);
		if (p_code[i] == REG_CODE && p_val[i] > 16)
			return (0);
	}
	return (1);
}
