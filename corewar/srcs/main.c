/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 15:17:22 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/24 13:28:04 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(-1);
}

int		main(int ac, char **av)
{
	t_vm		*vm;
	int			fight;

	if (ac <= 1)
		ft_error("ERROR: Bad arg number");
	ft_printf("Introducing contestants...\n");
	vm = boot_vm();
	check_args(ac, av, vm);
	if (vm->nbr_champs <= 0)
		ft_error("ERROR: Bad champ nbr");
	place_champions(vm);
	if (vm->o_graphic)
		init_display(vm->nbr_champs);
	fight = 1;
	while ((fight = start_fight(vm)))
		;
	if (vm->o_graphic)
		endwin();
	ft_printf("Contestant %d, \"%s\", has won !\n",
				vm->champ[vm->last_alive].id,
				vm->champ[vm->last_alive].name);
	return (0);
}
