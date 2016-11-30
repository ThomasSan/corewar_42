/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_lldi_sti.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:20:46 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/30 13:39:01 by ybeaure          ###   ########.fr       */
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
	int		1calculmamen;

	if (check_params(11, p_code, p_val))
	{
		registre = vm->champ[vm->ram[pro->pc].owner].reg[p_val[0] - 1];
		add = p_code[1] == REG_CODE ? vm->champ[vm->ram[pro->pc].owner].reg[p_val[1] - 1] : (signed short)p_val[1];
		add = add + p_code[2] == REG CODE ? vm->champ[vm->ram[pro->pc].owner].reg[p_val[2] - 1] : (signed short)p_val[2];
		i = 3
			while (i >= 0)
			{
				1calculmamen = (pro->pc + (add % IDX_MOD) + i + MEM_SIZE) % MEM_SIZE;	
				vm->ram[1calculmamen].value = registre % 256;
				registre = registre >> 8;
				vm->ram[1calculmamen].owner = vm->ram[pro->pc].owner;
			}
	}
}
