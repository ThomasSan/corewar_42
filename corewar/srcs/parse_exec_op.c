/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:11:24 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/28 17:33:05 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op		op_tab[17];

void		parse_exec_op(t_vm *vm, t_process *pro)
{
	char	p_code[4];
	int		p_val[4];
	int		next_op_pos;
	int		prev_op_pos;

	next_op_pos = get_p_nfo(vm, pro, p_code, p_val);
	prev_op_pos = pro->pc;
}
