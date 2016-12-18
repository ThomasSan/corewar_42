/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:15:12 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 18:46:30 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_ld(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{
	if (check_params(2, p_code, p_val))
	{
		pro->reg[p_val[1] - 1] = get_new_p_val(pro, vm, p_val[0], p_code[0]);
		if (pro->reg[p_val[1] - 1])
			pro->carry = 0;
		else
			pro->carry = 1;
	}
}

void		ft_st(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{
	int		i;
	int		reg;

	if (check_params(3, p_code, p_val))
	{
		if (p_code[1] == REG_CODE && p_val[1] <= REG_NUMBER)
			pro->reg[p_val[1] - 1] = pro->reg[p_val[0] - 1];
		else
		{
			reg = pro->reg[p_val[0] - 1];
			i = 4;
			while (--i >= 0)
			{
				vm->ram[(pro->pc + ((signed short)p_val[1] % IDX_MOD) + i + MEM_SIZE) % MEM_SIZE].value = reg % 256;
				reg = reg >> 8;
				vm->ram[(pro->pc + ((signed short)p_val[1] % IDX_MOD) + i + MEM_SIZE) % MEM_SIZE].champ = pro->champ;
			}
		}
	}
}

void		ft_lld(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{
	if (check_params(13, p_code, p_val))
	{
		pro->reg[p_val[1] - 1] = get_new_lp_val(pro, vm, p_val[0], p_code[0]);
		if (pro->reg[p_val[1] - 1])
			pro->carry = 0;
		else
			pro->carry = 1;
	}
}
