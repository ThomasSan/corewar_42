/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:18:35 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/30 14:37:09 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_add(t_vm *vm, t_process *pr, char p_code[4], int p_val[4])
{
	(void)vm;
	(void)pr;
	(void)p_code;
	(void)p_val;
}

void		ft_sub(t_vm *vm, t_process *pr, char p_code[4], int p_val[4])
{
	(void)vm;
	(void)pr;
	(void)p_code;
	(void)p_val;
}

void		ft_and(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(6, p_code, p_val))
	{
		vm->champs[vm->ram[pro->pc].owner].reg[p_val[2] - 1] = get_new_p_val(vm, pro, p_code[0], p_val[0]) &
			get_new_p_val(vm, pro, p_code[1], p_val[1]);
		if (vm->champs[vm->ram[pro->pc].owner].reg[p_val[2] - 1])
			pro->carry = 1;
		else
			pro->carry = 0;
	}
}
