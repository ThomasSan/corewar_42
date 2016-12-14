/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:17:21 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/14 16:28:53 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ft_live(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(1, p_code, p_val))
	{
//		if ((p_val[0] < 1) || (p_val[0] > 4))
		if ((p_val[0] != vm->champs[0].n_code) &&
				p_val[0] != vm->champs[1].n_code &&
				(vm->champs[2].used && p_val[0] != vm->champs[2].n_code) &&
				(vm->champs[3].used && p_val[0] != vm->champs[3].n_code))
		{
//			pro->lives++;
			return ;
		}
		vm->last_to_live = p_val[0];
		pro->lives++;
		if (!vm->option_graph)
		{
			ft_printf("%s%#X%s%s%s", "Le joueur ", p_val[0], " [",
					vm->champs[
					get_index_champ(vm, vm->champs, p_val[0])].header.prog_name,
					"] est en vie.");
			if (vm->option_cycle)
				ft_printf(" cycle : %d", vm->cycle.cycles);
			write(1, "\n", 1);
		}
	}
}
