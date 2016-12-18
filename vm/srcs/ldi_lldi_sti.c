/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_lldi_sti.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:20:46 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 19:04:22 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_ldi(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{
	int		add;
	int		i;

	if (check_params(10, p_code, p_val))
	{
		add = p_code[0] == REG_CODE ? pro->reg[p_val[0] - 1] : (signed short)p_val[0];
		add += p_code[1] == REG_CODE ? pro->reg[p_val[1] - 1] : (signed short)p_val[1];
		i = -1;
		pro->reg[p_val[2] - 1] = 0;
		while (++i < 4)
		{
			pro->reg[p_val[2] - 1] = pro->reg[p_val[2] - 1] << 8;
			pro->reg[p_val[2] - 1] += vm->ram[(pro->pc + (add % IDX_MOD) + i + MEM_SIZE) % MEM_SIZE].value;
		}
	}
}

void		ft_lldi(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{
	int		add;
	int		i;

	if (check_params(14, p_code, p_val))
	{
		add = p_code[0] == REG_CODE ? pro->reg[p_val[0] - 1] : (signed short)p_val[0];
		add += p_code[1] == REG_CODE ? pro->reg[p_val[1] - 1] : (signed short)p_val[1];
		i = -1;
		pro->reg[p_val[2] - 1] = 0;
		while (++i < 4)
		{
			pro->reg[p_val[2] - 1] = pro->reg[p_val[2] - 1] << 8;
			pro->reg[p_val[2] - 1] += vm->ram[(pro->pc + add + i + MEM_SIZE) % MEM_SIZE].value;
		}
		if (pro->reg[p_val[2] - 1])
			pro->carry = 0;
		else
			pro->carry = 1;
	}
}

void		ft_sti(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{

	int		add;
	int		i;
	int		reg;

	if (check_params(11, p_code, p_val))
	{
		reg = pro->reg[p_val[0] - 1];
		add = p_code[1] == REG_CODE ? pro->reg[p_val[1] - 1] : (signed short)p_val[1];
		add += p_code[2] == REG_CODE ? pro->reg[p_val[2] - 1] : (signed short)p_val[2];
		i = 4;
		while (--i >= 0)
		{
			vm->ram[(pro->pc + (add % IDX_MOD) + i + MEM_SIZE) % MEM_SIZE].value = reg % 256;
			reg = reg >> 8;
			vm->ram[(pro->pc + (add % IDX_MOD) + i + MEM_SIZE) % MEM_SIZE].champ = pro->champ;
		}
	}
}
