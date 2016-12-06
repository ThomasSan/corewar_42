/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:44:24 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/06 10:19:51 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			(*exec_op[17])(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]) = 
{
	ft_live,
	ft_ld,
	ft_st,
	ft_add,
	ft_sub,
	ft_and,
	ft_or,
	ft_xor,
	ft_zjmp,
	ft_ldi,
	ft_sti,
	ft_fork,
	ft_lld,
	ft_lldi,
	ft_lfork,
	ft_aff
};

static int		get_arg(t_vm *vm, int ac, char **av)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "--help") || !ft_strcmp(av[i], "-h"))
			return (-1);
		if (!ft_strcmp(av[i], "-n"))
			vm->option_graph = true;
		else if (!ft_strrncmp(av[i], ".cor", 4))
		{
			if (vm->nb_champ == MAX_PLAYERS)
				exit_corewar_msg(vm, "Too Much Champions !\n");
			get_champ(vm, &vm->champs[vm->nb_champ], av[i]);
			vm->nb_champ++;
		}
		i++;
	}
	if (vm->nb_champ < 2)
		exit_corewar_msg(vm, "Not enouth champions\n");
	return (0);
}

int				main(int argc, char **argv)
{
	t_vm	vm;
	t_process	*pro;

	init_vm(&vm);
	if (get_arg(&vm, argc, argv) == -1)
		exit_corewar_msg(&vm, "help:\n-n : use displayer\n");

	init_start(&vm);

	display_debug_champ(vm.champs, 0);
	display_debug_champ(vm.champs, 1);
	display_debug_champ(vm.champs, 2);
	display_debug_champ(vm.champs, 3);
	//	display_debug_ram(vm.ram);

	//	pro.pc = 0;
	//	while (1)
	while(1)
	{
		dprintf(2, "%s %#x\n", "val =",vm.ram[0].value);
		dprintf(2, "%s %#x\n", "owner =",vm.ram[0].owner);
		dprintf(2, "%s %#x\n", "val =",vm.ram[1].value);
		dprintf(2, "%s %#x\n", "owner =",vm.ram[1].owner);
		dprintf(2, "%s %#x\n", "val =",vm.ram[2].value);
		dprintf(2, "%s %#x\n", "owner =",vm.ram[2].owner);
		dprintf(2, "%s %#x\n", "val =",vm.ram[3].value);
		dprintf(2, "%s %#x\n", "owner =",vm.ram[3].owner);

		pro = vm.process;
			while (pro)
			{
				parse_exec_op(&vm, pro);
				pro = pro->next;
			}
		display_debug_ram(vm.ram);
		usleep(900000);
	}
	return (0);
}
