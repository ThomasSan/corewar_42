/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 18:20:55 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 18:26:19 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op	g_op_tab[17];

int			loop_ram(int val)
{
	int		ret;

	ret = val;
	while (ret < 0)
		ret = MEM_SIZE + ret;
	if (ret >= MEM_SIZE)
		ret = val % MEM_SIZE;
	return (ret);
}

int				check_params(char opcode, char p_code[4], int p_val[4])
{
	int		i;

	opcode--;

	i = -1;
	if (opcode > 15)
		return (0);
	while (++i < g_op_tab[(int)opcode].nbr_param)
	{
		if ((g_op_tab[(int)opcode].p_types[i] >> (p_code[i] - 1)) % 2 == 0)
			return (0);
		if (p_code[i] == REG_CODE && p_val[i] > 16)
			return (0);
	}
	return (1);
}

int				get_new_p_val(t_pro *pro, t_vm *vm, int p_val, int p_code)
{
	int		ret;

	ret = 0;
	if (p_code == T_REG)
		ret = pro->reg[p_val - 1];
	else if (p_code == IND_CODE)
		ret = vm->ram[loop_ram(pro->pc + (p_val % IDX_MOD))].value;
	else
		ret = p_val;
	return (ret);
}

int			get_new_lp_val(t_pro *pro, t_vm *vm, int p_val, int p_code)
{
	int		ret;

	ret = 0;
	if (p_code == T_REG)
		ret = pro->reg[p_val - 1];
	else if (p_code == IND_CODE)
		ret = vm->ram[loop_ram(pro->pc + p_val)].value;
	else
		ret = p_val;
	return (ret);
}
