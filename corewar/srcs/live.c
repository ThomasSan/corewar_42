/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:17:21 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/07 15:20:09 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_live(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(1, p_code, p_val))
	{
		vm->last_to_live = p_val[0] - 10;
		pro->lives++;
	ft_printf("%s%d%s%s\n", "Le joueur ", (p_val[0] - 10), " [", vm->champs[p_val[0] - 10].header.prog_name, "] est en vie");
//		ft_printf("%s%d%s%s%s\n", "Le joueur ", vm->last_to_live, " [", vm->champs[vm->last_to_live].header.prog_name, "] est en vie");
	}
}
