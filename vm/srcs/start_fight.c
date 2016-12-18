/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_fight.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 21:42:10 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 18:20:02 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ram_dump(t_ram *ram)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < MEM_SIZE)
	{
		if (ram[i].value <= 15)
			ft_putchar('0');
		ft_putstr(ft_base16(ram[i].value));
		i++;
		j++;
		if (j == 32)
		{
			ft_putchar('\n');
			j = 0;
		}
		else
			ft_putchar(' ');
	}
}

void	fight(t_cycle *cycle, t_vm *vm)
{
	int		kfight;

	kfight = 42;
	while (kfight)
	{
		exec_pro(cycle->pro, vm);
		kfight = update_cycle(cycle, vm);
		//		if (vm->o_graphic == 1)
		//pierre;
	}
	//	if (vm->o_graphic == 1)
	//pierre;
	ft_putstr("Le joueur ");
	ft_putnbr(vm->champs[vm->last_to_live].number);
	ft_putstr(" (");
	ft_putstr(vm->champs[vm->last_to_live].header.prog_name);
	ft_putstr(") a gagner.\n");
}

static void		delete_cycle(t_cycle *cycle, t_vm *vm)
{
	if (cycle->pro)
	{
		while(*(cycle->pro))
			kill_pro(*(cycle->pro), vm);
		free(cycle->pro);
	}
	free(cycle);
}

void	start_fight(t_vm *vm)
{
	vm->cycle = malloc(sizeof(t_cycle));
	init_cycle(vm->cycle, vm);
	//	if (vm->o_graphic == 1)
	//	pierre
	//	else
//	ram_dump(vm->ram);
	fight(vm->cycle, vm);
	delete_cycle(vm->cycle, vm);
}
