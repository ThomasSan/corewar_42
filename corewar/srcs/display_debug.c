/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 19:03:08 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/10 19:03:20 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			display_debug_reg(int reg[REG_NUMBER])
{
	int		i;

	i = -1;
	write(1, "\n", 1);
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
}

void			display_debug_ram(t_ram *ram, int cycle)
{
	int		len;
	int		i;

	len = 1;
	i = -1;
	ft_printf("\n----- RAM %d -----\n\n", cycle);
	while (++i < MEM_SIZE)
	//while(++i < 100)
	{
		if (ram[i].executed == 1)
			ft_printf("\x1b[30m\x1b[47m%.2x\x1b[0m ", ram[i].value);
		else
		{
			if (ram[i].owner == -1)
				ft_printf("%.2x ", ram[i].value);
			else if (ram[i].owner == 0)
				ft_printf("\033[0;32m%.2x\033[0m ", ram[i].value);
			else if (ram[i].owner == 1)
				ft_printf("\033[0;34m%.2x\033[0m ", ram[i].value);
			else if (ram[i].owner == 2)
				ft_printf("\033[0;31m%.2x\033[0m ", ram[i].value);
			else if (ram[i].owner == 3)
				ft_printf("\033[0;35m%.2x\033[0m ", ram[i].value);
			else
				ft_printf("\033[0;34m%.2x\033[0m ", ram[i].value);
		}
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
		ft_printf("\n----- PROCESS nº%d -----\npc : %d\ncurr_op : %d\n"
				"cycle_to_exec : %d\ncarry : %d\n", ++i, pro->pc, pro->curr_op,
				pro->cycles_to_exec, pro->carry);
		ft_putstr("\n");
		display_debug_reg(pro->reg);
		pro = pro->next;
		break;
	}
}
