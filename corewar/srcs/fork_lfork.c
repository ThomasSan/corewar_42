/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:22:46 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/06 11:47:07 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_fork(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	int		pc;

	if (check_params(12, p_code, p_val))
	{
		display_debug_ram(vm->ram);
		pc = (pro->pc + ((signed short)p_val[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE;
		add_process(&vm->process, pc, vm->ram[pc].value, pro->carry);
	}
}

void		ft_lfork(t_vm *vm, t_process *pr, char p_code[4], int p_val[4])
{
	(void)vm;
	(void)pr;
	(void)p_code;
	(void)p_val;
}
