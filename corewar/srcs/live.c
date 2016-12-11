/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:17:21 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/11 17:48:47 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_live(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(1, p_code, p_val))
	{
		if ((p_val[0] - 10) < 0 || (p_val[0] - 10 > 4))
			return ;
		vm->last_to_live = p_val[0] - 10;
		pro->lives++;
		if (!vm->option_graph)
		{
			ft_printf("%s%d%s%s%s\n", "Le joueur ", (p_val[0] - 10), "	[",
					vm->champs[p_val[0] - 10].header.prog_name, "] est en vie");
		}
	}
}
