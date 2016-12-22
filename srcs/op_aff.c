/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:09:42 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/22 16:30:15 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_aff(t_process *pro, t_vm *vm, char **p_val, char *p_type)
{
	int			str;

	(void)vm;
	if (p_type[0] == REG_CODE && check_p_val(p_val[0]))
	{
		str = c_int(pro->reg[c_single_int(p_val[0][0]) - 1]) % IDX_MOD;
		if (vm->o_graphic == 0 && vm->print_live == 1)
			write(1, &str, 4);
	}
}
