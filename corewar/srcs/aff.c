/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:24:27 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/30 13:34:40 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_aff(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(16, p_code, p_val) && !vm->option_graph)
	{
		write(1, "aff : ", 6);
		ft_putchar(vm->champ[vm->ram[pro->pc].owner].reg[p_val[0] - 1] % 256);
		ft_putchar('\n');
	}
}
