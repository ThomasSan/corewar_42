/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:23:44 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/10 18:12:57 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_zjmp(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (pro->carry == 1 && check_params(9, p_code, p_val))
	{
		pro->pc = (pro->pc + ((signed short)p_val[0] % IDX_MOD)
				+ MEM_SIZE) % MEM_SIZE;
	}
}
