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
#include <time.h>

void		fill_tab(t_memory *ram)
{
	int		i;
	int		x;
	int		y;
	char	*charhex;

	i = -1;
	y = 1;
	x = 1;
	move(y, x);
	while (++i < MEM_SIZE)
	{
		if (x >= SQUARE_WIDTH)
		{
			y++;
			x = 1;
		}
		move(y, x);
		print_mem_value(ram, i);
		x += 3;
	}
}

void		players_infos(t_champ *champ, int nbr_champs)
{
	int		i;
	int		y;

	i = 0;
	y = 18;
	while (i < MAX_PLAYERS)
	{
		if (champ[i].id > 0)
		{
			move(y, 250);
			printw("Player %d :", i);
			move(y, 261);
			attron(COLOR_PAIR(champ[i].id));
			printw("%s", champ[i].name);
			attroff(COLOR_PAIR(champ[i].id));
			if (champ[i].comment[0] != '\0')
			{
				move(y + 1, 250);
				printw("comment : %s", champ[i].comment);
			}
			y += 3;
		}
		i++;
	}
}

void		display_info(t_vm *vm)
{
	move(5, 250);
	printw("Cycle per seconds : %d", 1000000 / vm->speed);
	move(6, 250);
	printw("speed : %lld", vm->speed);
	move(10, 250);
	printw("Cycle : %d", vm->curr_cycle);
	move(11, 250);
	printw("Processes : %d", vm->nbr_champs);
	players_infos(vm->champ, vm->nbr_champs);
	move(13, 250);
	printw("CYCLE_TO_DIE : %d", vm->cycle_to_die);
	move(14, 250);
	printw("CYCLE_DELTA : %d", CYCLE_DELTA);
	move(15, 250);
	printw("NBR_LIVE : %d", vm->nbr_live);
	move(16, 250);
	printw("MAX_CHECKS : %d", MAX_CHECKS);
}

int			display_loop(t_vm *vm)
{
	int		key;
	int		my;
	int		mx;

	key = -1;
	erase();
	box_around(0, 0, SQUARE_HEIGHT, SQUARE_WIDTH);
	move(SQUARE_HEIGHT + 2, 0);
	fill_tab(vm->ram);
	display_info(vm);
	key = getch();
	move(40, 250);
	printw("time : %lld", clock());
	refresh();
	return (key);
}

int			display(t_vm *vm)
{
	int		key;

	key = -1;
	if ((key = display_loop(vm)))
	{
		if (key == KEY_NEWLINE || key == KEY_Q)
			return (0);
		if (key == KEY_PLUS && vm->speed - DELTA_SPEED > 0)
			vm->speed -= DELTA_SPEED;
		if (key == KEY_MINUS && vm->speed < SLOWEST_SPEED)
			vm->speed += DELTA_SPEED;
		if (key == KEY_SPACE)
			vm->paused = (vm->paused == 0) ? 1 : 0;
	}
	return (1);
}
