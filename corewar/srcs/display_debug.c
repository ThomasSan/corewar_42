/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 12:16:39 by cchameyr          #+#    #+#             */
/*   Updated: 2016/12/07 11:27:17 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			display_debug_reg(int reg[REG_NUMBER])
{
	int		i;

	i = -1;
	while (++i < REG_NUMBER)
		ft_printf("|    R%.2d   ", i + 1);
	ft_putstr("|\n");
	i = -1;
	while (++i < REG_NUMBER)
		ft_printf("| %.8X ", reg[i]);
	ft_putstr("|\n");
}

void			display_debug_champ(t_champ *champs, int number)
{
	int		i;
	int		cpt;

	if (champs[number].pos == -1)
		return ((void)ft_printf("ERROR : CHAMPION %d CAN'T BE READ\n",
					number + 1));
	ft_printf("\n----- CHAMPION %d -----\n", number + 1);
	ft_printf("magic number : %#x\n", champs[number].header.magic);
	ft_printf("prog_name : %s\n", champs[number].header.prog_name);
	ft_printf("prog_size : %d\n", champs[number].header.prog_size);
	ft_printf("comment : %s\n", champs[number].header.comment);
	ft_putstr("CONTENT PROG\n");
	i = -1;
	cpt = 0;
	while (++i < champs[number].len)
	{
		ft_printf("%.2x ", champs[number].data[i]);
		if (cpt++ > 64)
		{
			write(1, "\n", 1);
			cpt = 0;
		}
	}
	write(1, "\n", 1);
	display_debug_reg(champs[number].reg);
}

void			display_debug_ram(t_ram *ram, int cycle)
{
	int		len;
	int		i;

	len = 1;
	i = -1;
	ft_printf("\n----- RAM %d -----\n\n", cycle);
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

void			display_debug_process(t_process *pro)
{
	int		i;

	i = 0;
	while (pro)
	{
		ft_printf("----- PROCESS nº%d -----\npc : %d\ncurr_op : %d\n"
				"cycle_to_exec : %d\ncarry : %d\n", ++i, pro->pc, pro->curr_op,
				pro->cycles_to_exec, pro->carry);
		ft_putstr("\n\n");
		pro = pro->next;
	}
}
