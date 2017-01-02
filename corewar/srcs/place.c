/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 18:02:14 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 16:42:30 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		get_new_pc(t_process *pro, int new)
{
	int		old;

	old = pro->last_pc;
	pro->last_pc = new;
	//visual
}

void		place_in_vm(t_vm *vm, t_champ *champ, int pc)
{
	int			size;
	char		*mem;
	t_process	*pro;

	pro = find_pro_id(vm->lst_champs, champ->id);
	size = champ->size;
	mem = champ->memory;
	pro->pc = pc;
	get_new_pc(pro, pc);
	ft_memcpy(&vm->memory[pc], mem, size);
}

void		order_champs(t_vm *vm, t_champ champ[MAX_PLAYERS])
{
	int		i;
	t_champ	tmp;

	i = 0;
	while (i < vm->nbr_champs)
		if (i > 0 && champ[i].id > champ[i - 1].id)
		{
			ft_memcpy(&tmp, &champ[i], sizeof(t_champ));
			ft_memcpy(&champ[i], &champ[i - 1], sizeof(t_champ));
			ft_memcpy(&champ[i - 1], &tmp, sizeof(t_champ));
			i--;
		}
		else
			i++;
	i = 0;
	while (i < vm->nbr_champs)
	{
		vm->champ[i].first_pc->order = i;
		vm->champ[i].first_pc->c = &(vm->champ[i]);
		i++;
	}
}

void		place_champions(t_vm *vm)
{
	int		vide;
	int		i;

	vide = MEM_SIZE / vm->nbr_champs;
	i = -1;
	order_champs(vm, vm->champ);
	while (++i < vm->nbr_champs)
		place_in_vm(vm, &vm->champ[i], vide * i);
}
