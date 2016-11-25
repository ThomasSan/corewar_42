/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:44:24 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/25 15:50:52 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

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
			{
				ft_putstr("Too much champions guy !\n");
				exit_corewar(vm);
			}
			add_champ(vm, av[i]);
		}
	}
}

int				main(int argc, char **argv)
{
	t_vm	vm;

	init_vm(&vm);
	if (get_arg(&vm, argc, argv) == -1)
	{
		ft_printf("help:\n-n : use displayer\n");
		exit_corewar(&vm);
	}
	return (0);
}
