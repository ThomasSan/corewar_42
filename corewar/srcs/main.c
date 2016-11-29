/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:44:24 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/29 13:49:12 by cchameyr         ###   ########.fr       */
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
			if (vm->nb_champ == 4)
				exit_corewar_msg(vm, "Too Much Champions !\n");
			get_champ(vm, &vm->champs[vm->nb_champ], av[i]);
			vm->nb_champ++;
		}
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_vm	vm;

	init_vm(&vm);
	if (get_arg(&vm, argc, argv) == -1)
		exit_corewar_msg(&vm, "help:\n-n : use displayer\n");
	parse_exec_op(&vm, NULL);
	return (0);
}
