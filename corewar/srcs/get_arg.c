/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:48:27 by cchameyr          #+#    #+#             */
/*   Updated: 2016/11/25 13:50:29 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		get_arg(t_vm *vm, int ac, char **av)
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
