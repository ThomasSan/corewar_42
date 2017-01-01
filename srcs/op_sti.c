/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:13:22 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/19 17:13:30 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_sti(t_process *pro, t_vm *vm, char **p_val, char *p_type)
{
	int		p_val1;
	int		p_val2;
	int		tmp;
	int		i;

	if (p_type[0] == REG_CODE && check_p_val(p_val[0]) && ((p_type[1] == REG_CODE && check_p_val(p_val[1])) || p_type[1] == DIR_CODE || p_type[1] == IND_CODE) && ((p_type[2] == REG_CODE && check_p_val(p_val[2])) || p_type[2] == DIR_CODE))
	{
		p_val1 = get_new_p_val_sh(pro, vm, p_val[1], p_type[1]);
		p_val2 = get_new_p_val_sh(pro, vm, p_val[2], p_type[2]);
		tmp = (p_val1 + p_val2) % IDX_MOD;
		tmp = pro->last_pc + tmp;
		i = c_single_int(p_val[0][0]) - 1;
		vm->memory[idx_ram(tmp)] = (char)pro->reg[i][3];
		vm->memory[idx_ram(tmp + 1)] = (char)pro->reg[i][2];
		vm->memory[idx_ram(tmp + 2)] = (char)pro->reg[i][1];
		vm->memory[idx_ram(tmp + 3)] = (char)pro->reg[i][0];
	}
}
