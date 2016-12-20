/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 19:46:55 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/20 19:57:54 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		exec_op(t_process *pro, t_vm *vm)
{
	char		p_type[4];
	char		*p_val[4];

	ft_bzero(p_type, 4);
	ft_bzero(p_val, 4 * sizeof(char*));
	if (pro->curr_op == 0)
		pro->curr_op = vm->memory[pro->pc];
	get_new_pc(pro, pro->pc);
	if (pro->curr_op > 0 && pro->curr_op <= 16 && pro->execute < vm->nbr_cycle[pro->curr_op - 1] - 1)
	{
		pro->execute += 1;
		return ;
	}
	pro->execute = 0;
	change_pc(pro, 1);
	//REPRENDRE ICI
}
