/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boot_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 20:15:16 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 20:11:56 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void		init_vm(t_vm **vm)
{
	(*vm)->av = NULL;
	(*vm)->o_dump = 0;
	(*vm)->o_graphic = 0;
	(*vm)->nbr_champs = 0;
	(*vm)->ram = NULL;
	(*vm)->dump_cycle = -1;
}

static void		check_arg(t_vm **vm, int ac, char **av)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (++i < ac && av[i][0] == '-')
	{
		if (ft_strcmp(av[i], "-d") == 0 && (*vm)->o_dump == 0)
		{
			if (ft_atoi(av[i + 1]) > 0 || ft_strcmp(av[i], "0") == 0)
			{
				(*vm)->o_dump = 1;
				(*vm)->dump_cycle = ft_atoi(av[++i]);
			}
			else
				ft_error("-d doit etre suivi par un unsigned int");
		}
		else if (ft_strcmp(av[i], "-g") == 0 && (*vm)->o_graphic == 0)
			(*vm)->o_graphic = 1;
		else if (ft_strcmp(av[i], "-n") == 0)
			break ;
		else
			ft_error("ERROR");
	}
	(*vm)->av = ft_arrsub(av, i, array_size(av) - i);
	(*vm)->nbr_champs = count_champs(*vm);
}


t_vm			*boot_vm(t_vm *vm, int ac, char **av)
{
	if (ac == 1)
		ft_error("Pas d'arguments");
	vm = malloc(sizeof(t_vm));
	init_vm(&vm);
	check_arg(&vm, ac, av);
	vm->ram = init_ram();
	vm->champs = init_champs(vm);
	put_champs_on_map(&vm);
	return (vm);
}
