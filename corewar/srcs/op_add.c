/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:08:03 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/22 16:05:39 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_add(t_process *pro, t_vm *vm, char **p_val, char *p_type)
{
	int			add;
	int			cp_val;

	(void)vm;
	if (p_type[0] == REG_CODE && p_type[1] == REG_CODE && p_type[2] == REG_CODE
			&& check_p_val(p_val[0]) &&
			check_p_val(p_val[1]) && check_p_val(p_val[2]))
	{
		add = c_int(pro->reg[c_single_int(p_val[0][0]) - 1]) +
			c_int(pro->reg[c_single_int(p_val[1][0]) - 1]);
		cp_val = c_single_int(p_val[2][0]) - 1;
		pro->reg[cp_val][0] = (char)(add >> 0);
		pro->reg[cp_val][1] = (char)(add >> 8);
		pro->reg[cp_val][2] = (char)(add >> 16);
		pro->reg[cp_val][3] = (char)(add >> 24);
		if (add == 0)
			pro->carry = 1;
		else
			pro->carry = 0;
	}
}
