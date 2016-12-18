/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:59:35 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 19:55:57 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op	g_op_tab[17];

void	new_pro(t_pro *n_pro, t_pro *pro, t_vm *vm, signed short p_val)
{
	int		i;

	n_pro->pc = (pro->pc + p_val + MEM_SIZE) % MEM_SIZE;
	if (p_val == 0xFFFF9000)
		return ;
	if (vm->ram[n_pro->pc].value <= 16)
	{
		n_pro->curr_op = vm->ram[n_pro->pc].value;
		n_pro->cycles_to_exec = g_op_tab[n_pro->curr_op - 1].nbr_cycles - 1;
	}
	else
	{
		n_pro->cycles_to_exec = 0;
		n_pro->curr_op = 0;
	}
	i = -1;
	while (++i < REG_NUMBER)
		n_pro->reg[i] = pro->reg[i];
	n_pro->carry = pro->carry;
	n_pro->start = pro->start;
	n_pro->next = *(pro->start);
	*(n_pro->start) = n_pro;
	n_pro->lives = pro->lives;
	n_pro->champ = pro->champ;

}

void		ft_fork(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{
	t_pro		*n_pro;

	if(check_params(12, p_code, p_val))
	{
		n_pro = malloc(sizeof(t_pro));
		new_pro(n_pro, pro, vm, ((signed short)p_val[0]) % IDX_MOD);
	}
}

void		ft_lfork(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{	
	t_pro		*n_pro;

	if (check_params(15, p_code, p_val))
	{
		n_pro = malloc(sizeof(t_pro));
		new_pro(n_pro, pro, vm, (signed short)p_val[0]);
	}
}
