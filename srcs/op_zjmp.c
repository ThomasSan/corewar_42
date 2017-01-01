/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:13:43 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/19 17:13:50 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_zjmp(t_process *pro, t_vm *vm, char **p_val, char *p_type)
{
	int		jump;

	(void)vm;
	if (p_type[0] == DIR_CODE && pro->carry == 1)
	{
		jump = (int)c_short_int(p_val[0]) % IDX_MOD;
		pro->pc = idx_ram(pro->last_pc + jump);
	}
}
