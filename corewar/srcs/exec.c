/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 19:46:55 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 16:34:09 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		get_p_type(char bit, char p_type[4], int opcode, t_process *pro)
{
	unsigned char tmp;

	if (opcode == 1 || opcode == 9 || opcode == 12 || opcode == 15)
	{
		p_type[0] = 2;
		return ;
	}
	tmp = bit;
	p_type[0] = tmp >> 6;
	tmp = bit << 2;
	p_type[1] = tmp >> 6;
	tmp = bit << 4;
	p_type[2] = tmp >> 6;
	tmp = bit << 6;
	p_type[3] = tmp >> 6;
	move_pc(pro, 1);
}

char		*cpy_val(t_vm *vm, int len, int idx)
{
	char	*p_val;
	int		i;

	p_val = ft_strnew(len + 1);
	i = -1;
	while (++i < len)
	{
		p_val[i] = vm->memory[idx_ram(idx)];
		idx++;
	}
	return (p_val);
}

void		get_p_val(t_process *pro, t_vm *vm, char p_type[4], char *p_val[4])
{
	int		i;

	i = -1;
	while (++i < vm->argc[pro->last_op - 1])
		if (p_type[i] == REG_CODE)
		{
			p_val[i] = cpy_val(vm, 1, pro->pc);
			move_pc(pro, 1);
		}
		else if (p_type[i] == DIR_CODE)
		{
			p_val[i] = cpy_val(vm, vm->size_arg[pro->last_op - 1], pro->pc);
			move_pc(pro, vm->size_arg[pro->last_op - 1]);
		}
		else if (p_type[i] == IND_CODE)
		{
			p_val[i] = cpy_val(vm, 2, pro->pc);
			move_pc(pro, 2);
		}
}

void		free_val(char *p_val[4])
{
	int		i;

	i = -1;
	while (++i < 4)
		if (p_val[i])
			ft_strdel(&p_val[i]);
}

void		exec_op(t_process *pro, t_vm *vm)
{
	char		p_type[4];
	char		*p_val[4];

	ft_bzero(p_type, 4);
	ft_bzero(p_val, 4 * sizeof(char*));
	if (pro->curr_op == 0)
		pro->curr_op = vm->memory[pro->pc];
	get_new_pc(pro, pro->pc);
	if (pro->curr_op > 0 && pro->curr_op <= 16 && pro->execute <
			vm->nbr_cycle[pro->curr_op - 1] - 1)
	{
		pro->execute += 1;
		return ;
	}
	pro->execute = 0;
	move_pc(pro, 1);
	pro->last_op = pro->curr_op;
	if (pro->curr_op > 0 && pro->curr_op < 17)
	{
		get_p_type(vm->memory[pro->pc], p_type, pro->curr_op, pro);
		get_p_val(pro, vm, p_type, p_val);
		vm->op_function[pro->curr_op - 1](pro, vm, p_val, p_type);
		free_val(p_val);
	}
	pro->curr_op = 0;
}
