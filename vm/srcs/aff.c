/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:24:27 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 19:03:45 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_aff(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{
	if (check_params(16, p_code, p_val) && vm->o_graphic == 0)
	{
		ft_putstr("aff : ");
		ft_putchar((char)pro->reg[p_val[0] - 1] % 256);
		ft_putchar('\n');
	}
}
