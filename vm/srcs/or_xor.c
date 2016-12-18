/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 19:04:32 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 18:33:33 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_xor(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{
	if (check_params(8, p_code, p_val))
	{
		pro->reg[p_val[2] - 1] = get_new_p_val(pro, vm, p_val[0], p_code[0]) ^ get_new_p_val(pro, vm, p_val[1], p_code[1]);
		if (pro->reg[p_val[2] - 1])
			pro->carry = 0;
		else
			pro->carry = 1;
	}
}

void		ft_or(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{	
	if (check_params(7, p_code, p_val))
	{
		pro->reg[p_val[2] - 1] = get_new_p_val(pro, vm, p_val[0], p_code[0]) | get_new_p_val(pro, vm, p_val[1], p_code[1]);
		if (pro->reg[p_val[2] - 1])
			pro->carry = 0;
		else
			pro->carry = 1;
	}
}
