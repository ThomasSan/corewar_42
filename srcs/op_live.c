/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:11:43 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 16:32:39 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include <stdio.h>

void		print_l(t_champ *champ)
{
	ft_printf("Le joueur %d (%s) est en vie\n", champ->id, champ->name);
}

void		op_live(t_process *pro, t_vm *vm, char **p_val, char *p_type)
{
	int			id;
	int			i;

	pro->alive = 1;
	if (p_type[0] == DIR_CODE)
	{
		id = c_int_rev(p_val[0]);
		vm->nbr_live++;
		i = 0;
		while (i < MAX_PLAYERS)
		{
			if (vm->champ[i].id == id && vm->champ[i].dead == 0)
			{
				vm->last_alive = i;
				if (!vm->o_graphic && vm->print_live == 1)
					print_l(&(vm->champ[i]));
			}
			i++;
		}
	}
}
