/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:13:33 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 16:35:15 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_sub(t_process *pro, t_vm *vm, char **p_val, char *p_type)
{
	int		dif;
	int		n_pval;

	(void)vm;
	if (p_type[0] == REG_CODE && p_type[1] == REG_CODE && p_type[2] ==
			REG_CODE && check_p_val(p_val[1]) && check_p_val(p_val[2]))
	{
		dif = c_int(pro->reg[c_single_int(p_val[0][0]) - 1]) -
			c_int(pro->reg[c_single_int(p_val[1][0]) - 1]);
		n_pval = c_single_int(p_val[2][0]);
		pro->reg[n_pval - 1][0] = (char)dif;
		pro->reg[n_pval - 1][1] = (char)(dif >> 8);
		pro->reg[n_pval - 1][2] = (char)(dif >> 16);
		pro->reg[n_pval - 1][3] = (char)(dif >> 24);
		if (dif == 0)
			pro->carry = 1;
		else
			pro->carry = 0;
	}
}
