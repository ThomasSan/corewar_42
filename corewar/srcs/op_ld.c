/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 27:11:07 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 16:33:53 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_ld(t_process *pro, t_vm *vm, char **p_val, char *p_type)
{
	int	p_val1;
	int	reg;

	if ((p_type[0] == IND_CODE || p_type[0] == DIR_CODE) && p_type[1] ==
			REG_CODE && check_p_val(p_val[1]))
	{
		reg = get_new_p_val(pro, vm, p_val[0], p_type[0]);
		p_val1 = c_single_int(p_val[1][0]) - 1;
		pro->reg[p_val1][0] = (char)reg;
		pro->reg[p_val1][1] = (char)(reg >> 8);
		pro->reg[p_val1][2] = (char)(reg >> 16);
		pro->reg[p_val1][3] = (char)(reg >> 24);
		if (reg == 0)
			pro->carry = 1;
		else
			pro->carry = 0;
	}
}
