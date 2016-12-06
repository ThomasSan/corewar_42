/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:22:46 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/06 11:13:55 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_fork(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(12, p_code, p_val))
	{
	add_process(&vm->process, ((pro->pc + ((signed short)p_val[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE), pro->curr_op, pro->carry);
	}
}

void		ft_lfork(t_vm *vm, t_process *pr, char p_code[4], int p_val[4])
{
	(void)vm;
	(void)pr;
	(void)p_code;
	(void)p_val;
}
