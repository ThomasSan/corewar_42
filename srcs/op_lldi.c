/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:12:11 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 16:41:31 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_lldi(t_process *pro, t_vm *vm, char **p_val, char *p_type)
{
	int		i;
	int		p_val1;
	int		p_val2;
	int		tmp;

	if (p_type[2] == REG_CODE && check_p_val(p_val[2]) && ((p_type[0] ==
					REG_CODE && check_p_val(p_val[0])) || p_type[0] ==
				DIR_CODE || p_type[0] == IND_CODE) && ((p_type[1] == REG_CODE
						&& check_p_val(p_val[1])) || p_type[1] == DIR_CODE))
	{
		p_val1 = get_new_p_val_sh(pro, vm, p_val[0], p_type[0]);
		p_val2 = get_new_p_val_sh(pro, vm, p_val[1], p_type[1]);
		tmp = (p_val1 + p_val2);
		tmp = pro->last_pc + tmp;
		i = c_single_int(p_val[2][0]) - 1;
		pro->reg[i][0] = (char)vm->memory[idx_ram(tmp + 3)];
		pro->reg[i][1] = (char)vm->memory[idx_ram(tmp + 2)];
		pro->reg[i][2] = (char)vm->memory[idx_ram(tmp + 1)];
		pro->reg[i][3] = (char)vm->memory[idx_ram(tmp)];
		if (*((int*)pro->reg[i]) == 0)
			pro->carry = 1;
		else
			pro->carry = 0;
	}
}
