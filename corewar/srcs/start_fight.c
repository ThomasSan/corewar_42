/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_fight.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 19:21:58 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 16:35:29 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		print_ram(t_vm *vm)
{
	int		i;

	if (vm->o_graphic)
		return ;
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i == 0)
			ft_putstr("0x");
		if (i % 64 == 0)
			ft_printf("%#.4x : ", i);
		ft_printf("%.2hhx ", vm->ram[i].offset);
		if (i % 64 == 63)
			ft_putchar('\n');
	}
}

void		check_champ(t_process *pro, t_vm *vm, t_lst *elem)
{
	if (pro->alive > 0)
		pro->alive = 0;
	else
	{
		vm->champ[pro->order].pc_number -= 1;
		vm->nbr_champs -= 1;
		get_new_pc(pro, -1);
		//graphic
		ft_lstdelin_memdel(&vm->lst_champs, elem);
	}
}

void		update_cycle(t_vm *vm)
{
	static int	last_update = -1;

	if (last_update >= vm->curr_cycle)
		return ;
	last_update = vm->curr_cycle;
	vm->cycle_to_die -= CYCLE_DELTA;
	if (vm->cycle_to_die < 0)
		vm->cycle_to_die = 0;
}

void		check_live(t_vm *vm)
{
	t_lst	*tmp;
	t_lst	*next;

	if (vm->nbr_live > NBR_LIVE)
	{
		vm->nbr_live = 0;
		update_cycle(vm);
	}
	if (vm->nbr_check > MAX_CHECKS)
	{
		vm->nbr_check = 0;
		update_cycle(vm);
	}
	vm->nbr_live = 0;
	vm->nbr_check += 1;
	vm->die_verif = 0;
	tmp = vm->lst_champs;
	while (tmp && vm->nbr_champs > 0)
	{
		next = tmp->next;
		check_champ(tmp->data, vm, tmp);
		tmp = next;
	}
}

int			start_fight(t_vm *vm)
{
	t_lst		*tmp;

	if (clock() > vm->processed_time && vm->paused == 0)
	{
		if (vm->nbr_champs <= 0)
		{
			ft_printf("Player  %d(%s) won\n", vm->champ[vm->last_alive].id,
					vm->champ[vm->last_alive].name);
			return (0);
		}
		if (vm->curr_cycle >= vm->cycle_to_exec && vm->cycle_to_exec >= 0)
		{
			print_ram(vm);
			return (0);
		}
		vm->die_verif += 1;
		vm->curr_cycle += 1;
		tmp = vm->lst_champs;
		while (tmp)
		{
			exec_op((t_process*)tmp->data, vm);
			tmp = tmp->next;
		}
		if (vm->die_verif >= vm->cycle_to_die)
			check_live(vm);
		vm->processed_time += vm->speed;
	}
	if (vm->o_graphic && !display(vm))
		return (0);
	return (1);
}
