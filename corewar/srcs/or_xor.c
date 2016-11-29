/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:19:38 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/29 18:03:53 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_xor(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(8, p_code, p_val))
	{
		pro->reg[p_val[2] - 1] = get_new_p_val(vm, pro, p_code[0], p_val[0]) ^ get_new_p_val(vm, pro, p_code[1], p_val[1]);
		if (pro->reg[p_val[2] - 1])
			pro->carry = 1;
		else
			pro->carry = 0;
	}
}

void		ft_or(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(7, p_code, p_val))
	{
		pro->reg[p_val[2] - 1] = get_new_p_val(vm, pro, p_code[0], p_val[0]) | get_new_p_val(vm, pro, p_code[1], p_val[1]);
		if (pro->reg[p_val[2] - 1])
			pro->carry = 1;
		else
			pro->carry = 0;
	}
}
