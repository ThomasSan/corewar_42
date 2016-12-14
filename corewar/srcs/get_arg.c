/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 10:47:03 by cchameyr          #+#    #+#             */
/*   Updated: 2016/12/14 16:08:43 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int		check_ncodes(t_vm *vm)
{
	int		i1;
	int		i2;

	i1 = -1;
	while (++i1 < vm->nb_champ)
	{
		i2 = -1;
		while (++i2 <= vm->nb_champ)
		{
			if (i1 == i2)
				;
			else if (vm->champs[i1].n_code == vm->champs[i2].n_code)
				return (_ERROR_);
		}
	}
	return (_SUCCESS_);
}

static int		n_option_on(t_vm *vm, char **av, int ac, int *i)
{
	if (*i + 1 >= ac)
		return (_ERROR_);
	if (ft_strishexa(av[++(*i)]))
	{
		if (ft_strstr(av[*i], "0x"))
			vm->champs[vm->nb_champ].n_code = ft_atoi_base(&av[*i][2], 16);
		else
			vm->champs[vm->nb_champ].n_code = ft_atoi_base(av[*i], 16);
		if (++(*i) >= ac)
			exit_corewar_msg(vm, "ERROR - Precise a champion\n");
		if (vm->nb_champ == MAX_PLAYERS)
			exit_corewar_msg(vm, "Too much champions !\n");
		get_champ(vm, &vm->champs[vm->nb_champ], av[*i]);
		if (!check_ncodes(vm))
			exit_corewar_msg(vm, "ERROR - Number specification are "
					"identical\n");
		vm->nb_champ++;
		return (_SUCCESS_);
	}
	else
	{
		ft_printf("ERROR - [%s] isn't a valid number\n", av[*i]);
		exit_corewar(vm);
	}
	return (_ERROR_);
}

static int		n_option_off(t_vm *vm, char *path)
{
	static int		n_code = 0xFFFFFFFF;

	if (!ft_strrncmp(path, ".cor", 4))
	{
		if (vm->nb_champ == MAX_PLAYERS)
			exit_corewar_msg(vm, "Too much champions !\n");
		get_champ(vm, &vm->champs[vm->nb_champ], path);
		vm->champs[vm->nb_champ].n_code = n_code--;
		vm->nb_champ++;
		return (_SUCCESS_);
	}
	else
		return (_ERROR_);
}

int				get_arg(t_vm *vm, int ac, char **av)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "--help") || !ft_strcmp(av[i], "-h"))
			return (-1);
		if (!ft_strcmp(av[i], "-c"))
			vm->option_cycle = true;
		else if (!ft_strcmp(av[i], "-g"))
			vm->option_graph = true;
		else if (!ft_strcmp(av[i], "-n") && n_option_on(vm, av, ac, &i))
			;
		else if (n_option_off(vm, av[i]))
			;
		else
			exit_corewar_msg(vm, "Use a .cor file\n");
		i++;
	}
	if (vm->nb_champ < 2)
		exit_corewar_msg(vm, "Not enouth champions\n");
	return (0);
}
