/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:10:52 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/29 17:16:28 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_fork(t_process *pro, t_vm *vm, char **p_val, char *p_type)
{
	short int	idx;
	t_process	*new;

	(void)p_type;
	idx = c_short_int(p_val[0]);
	idx = idx % IDX_MOD;
	new = ft_memalloc(sizeof(t_process));
	ft_memcpy(new, pro, sizeof(t_process));
	new->pc = idx_ram(idx + new->last_pc);
	new->execute = 0;
	new->curr_op = 0;
	new->inside = vm->curr_cycle;
	get_new_pc(new, new->pc);
	create_process(vm, new);
	vm->nbr_champs += 1;
	vm->champ[pro->order].pc_number += 1;
}

void		op_lfork(t_process *pro, t_vm *vm, char **p_val, char *p_type)
{
	short int	idx;
	t_process	*new;

	(void)p_type;
	idx = c_short_int(p_val[0]);
	new = ft_memalloc(sizeof(t_process));
	ft_memcpy(new, pro, sizeof(t_process));
	new->pc = idx_ram(idx + new->last_pc);
	new->execute = 0;
	new->curr_op = 0;
	new->inside = vm->curr_cycle;
	get_new_pc(new, new->pc);
	create_process(vm, new);
	vm->nbr_champs += 1;
	vm->champ[pro->order].pc_number += 1;
}
