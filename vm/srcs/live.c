/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:17:21 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 19:06:07 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			check_champ_nbr(t_vm *vm, int p_val, t_champs *champ)
{
	short i;

	i = -1;
	while (++i < vm->nbr_champs)
	{
		if (champ[i].number == p_val)
			return (i);
	}
	return (-1);
}

void		ft_live(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4])
{
	int			calcul;


	calcul = 0;
	if (check_params(1, p_code, p_val))
	{
		if (check_champ_nbr(vm, p_val[0], vm->champs) != -1)
			vm->last_to_live = check_champ_nbr(vm, p_val[0], vm->champs);
		pro->lives++;
		vm->nbr_live++;
		if (vm->o_graphic == 0 && check_champ_nbr(vm, p_val[0], vm->champs) != -1)
		{
			calcul = check_champ_nbr(vm, p_val[0], vm->champs);
			ft_putstr("Le joueur ");
			ft_putnbr(vm->champs[calcul].number);
			ft_putstr(" (");
			ft_putstr(vm->champs[calcul].header.prog_name);
			ft_putendl(") est en vie");
		}
	}
}
