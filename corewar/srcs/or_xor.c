/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:19:38 by ybeaure           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2016/12/10 18:10:53 by ybeaure          ###   ########.fr       */
=======
/*   Updated: 2016/12/09 18:33:04 by cchameyr         ###   ########.fr       */
>>>>>>> e0a2ebede6bcc32c88a42d5a51a9b25f3970c73c
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_xor(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(8, p_code, p_val))
	{
<<<<<<< HEAD
		pro->reg[p_val[2] - 1] = get_new_p_val(vm, pro, p_code[0], p_val[0])
			^ get_new_p_val(vm, pro, p_code[1], p_val[1]);
		if (pro->reg[p_val[2] - 1] == 0)
=======
		pro->reg[p_val[2] - 1] = get_new_p_val(vm, pro, p_code[0], p_val[0]) ^ get_new_p_val(vm, pro, p_code[1], p_val[1]);


/*
		if (get_new_p_val(vm, pro, p_code[0], p_val[0]) == 14 && i == 0)
		{
			i = 0;
			vm->A_supprimer = pro;
		}
*/


		if (pro->reg[p_val[2] - 1] == 0)
		{
//			ft_printf("CARRY = 1\ncycle : %d\n", vm->cycle.cycles);
>>>>>>> e0a2ebede6bcc32c88a42d5a51a9b25f3970c73c
			pro->carry = 1;
		else
<<<<<<< HEAD
			pro->carry = 0;
=======
		{
/*			if (pro == vm->A_supprimer)
			{
				ft_printf("CARRY = 0\ncycle : %d\nvalue REG : %d\n", vm->cycle.cycles, pro->reg[p_val[2] - 1]);
				ft_printf("gnpv 1 : %#x\ngnpv 2 : %#x\n", get_new_p_val(vm, pro, p_code[0], p_val[0]), get_new_p_val(vm, pro, p_code[1], p_val[1]));
				ft_printf("p_val[1] : %#X\n", p_val[1]);
			}
*/			pro->carry = 0;
		}

>>>>>>> e0a2ebede6bcc32c88a42d5a51a9b25f3970c73c
	}
}

void		ft_or(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(7, p_code, p_val))
	{
		pro->reg[p_val[2] - 1] = get_new_p_val(vm, pro, p_code[0], p_val[0])
			| get_new_p_val(vm, pro, p_code[1], p_val[1]);
		if (pro->reg[p_val[2] - 1])
			pro->carry = 0;
		else
			pro->carry = 1;
	}
}
