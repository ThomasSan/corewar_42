/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:13:13 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 16:33:30 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_st(t_process *pro, t_vm *vm, char **p_val, char *p_type)
{
	int			tmp;
	int			reg;
	int			pc;

	if (p_type[0] == REG_CODE && check_p_val(p_val[0]) && p_type[1] == IND_CODE)
	{
		tmp = c_short_int(p_val[1]) % IDX_MOD;
		reg = c_single_int(p_val[0][0]) - 1;
		pc = pro->last_pc + tmp;
		vm->memory[idx_ram(pc + 3)] = pro->reg[reg][0];
		vm->memory[idx_ram(pc + 2)] = pro->reg[reg][1];
		vm->memory[idx_ram(pc + 1)] = pro->reg[reg][2];
		vm->memory[idx_ram(pc)] = pro->reg[reg][3];
	}
	else if (p_type[0] == 1 && check_p_val(p_val[0]) && p_type[1] == 1 &&
			check_p_val(p_val[0]))
		copy_registre(pro, c_single_int(p_val[1][0]) - 1,
				c_single_int(p_val[0][0]) - 1);
}
