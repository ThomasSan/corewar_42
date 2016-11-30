/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 12:16:39 by cchameyr          #+#    #+#             */
/*   Updated: 2016/11/30 12:48:53 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	display_debug_champ(t_champ *champs, int number)
{
	int		i;
	int		cpt;

	ft_printf("----- CHAMPION %d -----\n", number);
	ft_printf("magic number : %#x\n", champs[number].header.magic);
	ft_printf("prog_name : %s\n", champs[number].header.prog_name);
	ft_printf("prog_size : %d\n", champs[number].header.prog_size);
	ft_printf("comment : %s\n", champs[number].header.comment);
	ft_putstr("----- CONTENT PROG -----\n");
	i = -1;
	cpt = 0;
	while (++i < champs[number].len)
	{
		ft_printf("%.2x ", champs[number].data[i]);
		if (cpt++ > 8)
		{
			write(1, "\n", 1);
			cpt = 0;
		}
	}
	write(1, "\n", 1);
}

void	display_debug_ram(t_ram *ram)
{
	int		len;
	int		i;

	len = 1;
	i = -1;
	ft_putstr("----- RAM -----\n\n");
	while (++i < MEM_SIZE)
	{
		if (ram[i].executed == 1)
			ft_printf("\x1b[30m\x1b[47m%.2x\x1b[0m ", ram[i].value);
		else
			ft_printf("%.2x ", ram[i].value);
		if (len >= 64)
		{
			write(1, "\n", 1);
			len = 0;
		}
		len++;
	}
}
