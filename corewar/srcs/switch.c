/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 16:33:40 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/22 17:11:39 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		get_new_p_val_noidx(t_process *pro, t_vm *vm, char *p_val, char p_type)
{
	int		n_pval;
	int		tmp;
	int		pc;
	char	tab[4];

	n_pval = 0;
	if (p_type == 1)
		n_pval = c_int(pro->reg[c_single_int(p_val[0]) - 1]);
	else if (p_type == 2)
		n_pval = c_int_rev(p_val);
	else if (p_type == 3)
	{
		tmp = c_short_int(p_val);
		pc = pro->last_pc + tmp;
		ft_bzero(tab, 4);
		tab[0] = (char)vm->memory[idx_ram(pc + 3)];
		tab[1] = (char)vm->memory[idx_ram(pc + 3)];
		tab[2] = (char)vm->memory[idx_ram(pc + 2)];
		tab[3] = (char)vm->memory[idx_ram(pc)];
		n_pval = *((int*)tab);
	}
	return (n_pval);
}

int		get_new_p_val(t_process *pro, t_vm *vm, char *p_val, char p_type)
{
	int		n_pval;
	int		tmp;
	int		pc;
	char	tab[4];

	n_pval = 0;
	if (p_type == 1)
		n_pval = c_int(pro->reg[c_single_int(p_val[0]) - 1]);
	else if (p_type == 2)
		n_pval = c_int_rev(p_val);
	else if (p_type == 3)
	{
		tmp = c_short_int(p_val) % IDX_MOD;
		pc = pro->last_pc + tmp;
		ft_bzero(tab, 4);
		tab[0] = (char)vm->memory[idx_ram(pc + 3)];
		tab[1] = (char)vm->memory[idx_ram(pc + 3)];
		tab[2] = (char)vm->memory[idx_ram(pc + 2)];
		tab[3] = (char)vm->memory[idx_ram(pc)];
		n_pval = *((int*)tab);
	}
	return (n_pval);
}

int		get_new_p_val_sh(t_process *pro, t_vm *vm, char *p_val, char p_type)
{
	int		n_pval;
	int		tmp;
	int		pc;
	char	tab[4];

	n_pval = 0;
	if (p_type == 1)
		n_pval = c_int(pro->reg[c_single_int(p_val[0]) - 1]);
	else if (p_type == 2)
		n_pval = (int)c_short_int(p_val);
	else if (p_type == 3)
	{
		tmp = c_short_int(p_val) % IDX_MOD;
		pc = pro->last_pc + tmp;
		ft_bzero(tab, 4);
		tab[0] = (char)vm->memory[idx_ram(pc + 3)];
		tab[1] = (char)vm->memory[idx_ram(pc + 2)];
		tab[2] = (char)vm->memory[idx_ram(pc + 1)];
		tab[3] = (char)vm->memory[idx_ram(pc)];
		n_pval = *((int*)tab);
	}
	return (n_pval);
}
