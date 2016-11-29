/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:19:38 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/29 11:49:43 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_xor(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(8, p_code, p_val))
	{
		pro->reg[p_val[2] - 1] = get_
	}
}

void		ft_or(t_vm *vm, t_process *pr, char p_code[4], int p_val[4])
{
	(void)vm;
	(void)pr;
	(void)p_code;
	(void)p_val;
}
