/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:24:27 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/29 08:06:26 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_aff(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(16, p_code, p_val) && !vm->option_graph)
		ft_printf("%s %c\n", "aff :", (pro->reg[p_val[0] - 1] % 256));
}
