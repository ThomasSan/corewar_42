/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_lldi_sti.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:20:46 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/01 17:16:18 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_ldi(t_vm *vm, t_process *pr, char p_code[4], int p_val[4])
{
	(void)vm;
	(void)pr;
	(void)p_code;
	(void)p_val;
}

void		ft_lldi(t_vm *vm, t_process *pr, char p_code[4], int p_val[4])
{
	(void)vm;
	(void)pr;
	(void)p_code;
	(void)p_val;
}

void		ft_sti(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	int		add;
	int		i;
	int		registre;
	int		calculmamen;


//	display_debug_ram(vm->ram);
	if (check_params(11, p_code, p_val))
	{
	display_debug_ram(vm->ram);
		registre = vm->champs[vm->ram[pro->pc].owner].reg[p_val[0] - 1];
		add = p_code[1] == REG_CODE ? vm->champs[vm->ram[pro->pc].owner].reg[p_val[1] - 1] : (signed short)p_val[1];
		add += p_code[2] == REG_CODE ? vm->champs[vm->ram[pro->pc].owner].reg[p_val[2] - 1] : (signed short)p_val[2];
		i = 4;
		while (--i >= 0)
		{
			calculmamen = (pro->pc + (add % IDX_MOD) + i + MEM_SIZE) % MEM_SIZE;	
			vm->ram[calculmamen].value = registre % 256;
			registre = registre >> 8;
			vm->ram[calculmamen].owner = vm->ram[pro->pc].owner;
		}
		display_debug_ram(vm->ram);
	}
}
