/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:15:12 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/05 13:54:23 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_ld(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(2, p_code, p_val))
	{
			YOLO
				dprintf(2, "%d\n", vm->ram[pro->pc].owner);
				dprintf(2, "%#x\n", (p_val[1] - 1));
				vm->champs[1].reg[p_val[1] - 1] = 0;
				//vm->champs[vm->ram[pro->pc].owner].reg[p_val[1] - 1] = 0;
			//	vm->champs[1].reg[p_val[1] - 1] = 0;
			YOLO2
		vm->champs[vm->ram[pro->pc].owner].reg[p_val[1] - 1] = get_new_p_val(vm, pro, p_val[0], p_code[0]); 
			YOLO2
		if (vm->champs[vm->ram[pro->pc].owner].reg[p_val[1] - 1])
		{
			pro->carry = 1;
		}
		else
		{
			pro->carry = 0;
		}
	}
}

void		ft_st(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	int		i;
	int		registre;
	int		calcul;

	if (check_params(3, p_code, p_val))
	{
		if (p_code[1] == REG_CODE && p_val[1] <= REG_NUMBER)
			vm->champs[vm->ram[pro->pc].owner].reg[p_val[1] - 1] = vm->champs[vm->ram[pro->pc].owner].reg[p_val[0] - 1];
		else
			registre = vm->champs[vm->ram[pro->pc].owner].reg[p_val[0] - 1];
		i = 4;
		while (--i >= 0)
		{
			calcul = (pro->pc + ((signed short)p_val[1] % IDX_MOD) + i + MEM_SIZE) % MEM_SIZE;
			vm->ram[calcul].value = registre % 256;
			registre = registre >> 8;
			vm->ram[calcul].owner = vm->ram[pro->pc].owner;
		}
	}
}

void		ft_lld(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(13, p_code, p_val))
	{
		vm->champs[vm->ram[pro->pc].owner].reg[p_val[1] - 1] = get_new_lp_val(vm, pro, p_val[0], p_code[0]);
		pro->carry = 0;
		if (vm->champs[vm->ram[pro->pc].owner].reg[p_val[1] - 1])
			pro->carry = 1;
	}
}
