/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:12:46 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 16:39:57 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_xor(t_process *pro, t_vm *vm, char **p_val, char *p_type)
{
	int		reg;
	int		i;
	int		p_val1;
	int		p_val2;

	if (p_type[2] == REG_CODE && check_p_val(p_val[2]) && ((p_type[0] ==
					REG_CODE && check_p_val(p_val[0])) || p_type[0] ==
				DIR_CODE || p_type[0] == IND_CODE) && ((p_type[1] == REG_CODE
						&& check_p_val(p_val[1])) || p_type[1] == DIR_CODE
					|| p_type[1] == IND_CODE))
	{
		p_val1 = get_new_p_val(pro, vm, p_val[0], p_type[0]);
		p_val2 = get_new_p_val(pro, vm, p_val[1], p_type[1]);
		reg = p_val1 ^ p_val2;
		i = c_single_int(p_val[2][0]) - 1;
		pro->reg[i][0] = (char)reg;
		pro->reg[i][1] = (char)(reg >> 8);
		pro->reg[i][2] = (char)(reg >> 16);
		pro->reg[i][3] = (char)(reg >> 24);
		if (reg == 0)
			pro->carry = 1;
		else
			pro->carry = 0;
	}
}
