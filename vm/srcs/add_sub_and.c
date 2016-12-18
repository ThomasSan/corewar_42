/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:18:35 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 18:32:09 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_add(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{

	vm->o_dump = vm->o_dump + 1 - 1;
	if (check_params(4, p_code, p_val))
	{
		pro->reg[p_val[2] - 1] = pro->reg[p_val[1] - 1] + pro->reg[p_val[0] - 1];
		if (pro->reg[p_val[2] - 1])
			pro->carry = 0;
		else
			pro->carry = 1;
	}
}

void		ft_sub(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{
	vm->o_dump = vm->o_dump + 1 - 1;
	if (check_params(5, p_code, p_val))
	{
		pro->reg[p_val[2] - 1] = pro->reg[p_val[0] - 1] - pro->reg[p_val[1] - 1];
		if (pro->reg[p_val[2] - 1])
			pro->carry = 0;
		else
			pro->carry = 1;
	}
}

void		ft_and(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{
	if (check_params(6, p_code, p_val))
	{
		pro->reg[p_val[2] - 1] = get_new_p_val(pro, vm, p_val[0], p_code[0]) & get_new_p_val(pro, vm, p_val[1], p_code[1]);
		if (pro->reg[p_val[2] - 1])
			pro->carry = 0;
		else
			pro->carry = 1;
	}
}
