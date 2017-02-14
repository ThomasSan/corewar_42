/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 15:17:22 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 16:32:00 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

char		*convert_dec_to_hex(int dec)
{
	char	*charhex;
	char	*hex;

	charhex = "0123456789ABCDEF";
	if (dec < 0)
		dec += 256;
	hex = (char*)malloc(sizeof(char) * 3);
	hex[0] = charhex[dec / 16];
	hex[1] = charhex[dec % 16];
	hex[2] = '\0';
	return (hex);
}

void		print_mem_value(t_memory *ram, int i)
{
	char	*charhex;

	charhex = convert_dec_to_hex(ram[i].offset);
	if (ram[i].owner_id > -1)
		attron(COLOR_PAIR(ram[i].owner_id));
	printw(" %s", charhex);
	if (ram[i].owner_id > -1)
		attroff(COLOR_PAIR(ram[i].owner_id));
	free(charhex);
}

void		box_around(int y, int x, int h, int w)
{
	int		j;

	move(y, x);
	addch(ACS_ULCORNER);
	j = 0;
	while (j++ < w)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	j = -1;
	while (j++ < h)
	{
		move(y + 1 + j, x);
		addch(ACS_VLINE);
		move(y + 1 + j, x + w + 1);
		addch(ACS_VLINE);
	}
	move(y + h + 1, x);
	addch(ACS_LLCORNER);
	j = 0;
	while (j++ < w)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void		init_color_pairs(int nbr_champs)
{
	int		i;

	i = 0;
	while (i < nbr_champs)
	{
		init_pair(i + 1, (i % 6) + 1, 0);
		init_pair(i + 11, 0, (i % 6) + 1);
		i++;
	}
}

void		init_display(int nb_champs)
{
	WINDOW * win;
	initscr();
	start_color();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	init_color_pairs(nb_champs);
}
