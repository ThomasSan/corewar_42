#include "../includes/corewar.h"
#include <time.h>

char		*convert_dec_to_hex(int dec)
{
	char	charHex[]="0123456789ABCDEF";
	char	*hex;

	if (dec < 0)
		dec += 256;
	hex = (char*)malloc(sizeof(char) * 3);
	hex[0] = charHex[dec / 16];
	hex[1] = charHex[dec % 16];
	hex[2] = '\0';
	return (hex);
}

void		boxAround( int y, int x, int h, int w ) {
    move( y, x );
    addch (ACS_ULCORNER);   // upper left corner
    int j;
    for (j = 0;  j < w;  ++j)
        addch (ACS_HLINE);
    addch (ACS_URCORNER);   // upper right

    for( j = 0; j < h; ++j ) 
    {
            move(y + 1 + j, x);
            addch (ACS_VLINE);
            move(y + 1 + j, x + w + 1);
            addch (ACS_VLINE);
    }
    move( y+h+1,x );
    addch (ACS_LLCORNER);   // lower left corner

    for (j = 0;  j < w;  ++j)
        addch (ACS_HLINE);
    addch (ACS_LRCORNER);   // lower right
}

void		fill_tab(t_memory *ram)
{
	int		i;
	int		x,y;
	char	*charHex;

	i = 0;
	y = 1;
	x = 1;
	move(y,x);
	while(i < MEM_SIZE)
	{
		if (x >= SQUARE_WIDTH)
		{
			y++;
			x = 1;
		}
		move(y,x);
		charHex = convert_dec_to_hex(ram[i].offset);
		/*if (ram[i].owner > -1)
		{
			if (ram[i].executed)
				attron(COLOR_PAIR(ram[i].owner + 11));
			else
				attron(COLOR_PAIR(ram[i].owner + 1));
		}*/
		printw(" %s", charHex);
		/*if (ram[i].owner > -1)
		{
			if (ram[i].executed)
				attroff(COLOR_PAIR(ram[i].owner + 11));
			else
				attroff(COLOR_PAIR(ram[i].owner + 1));
		}*/
		free(charHex);
		x += 3;
		i++;
	}
}
/* redesign needed
int			process_count(t_lst *lst)
{
	t_lst	*tmp;
	int		count;

	count = 0;
	tmp = lst;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}*/

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
			attron(COLOR_PAIR(champ[i].id ));
			printw("%s, id : %d", champ[i].name, champ[i].id);
			attroff(COLOR_PAIR(champ[i].id));
			move(y + 1, 250);
			printw("Last live : ");
			move(y + 2, 250);
			printw("lives current : ");
			y += 4;
		}
		i++;
	}
}

void		display_info(t_vm *vm)
{
	move(5, 250);
	printw("Cycle per seconds : %d", 1000000/vm->speed);
	move(6, 250);
	printw("speed : %lld", vm->speed);
	move(10, 250);
	printw("Cycle : %d", vm->curr_cycle);
	move(11, 250);
	printw("Processes : %d", vm->nbr_champs);
	players_infos(vm->champ, vm->nb_champs);
	// move(13 + (vm->nb_champs * 4), 250);
	move(13, 250);
	printw("CYCLE_TO_DIE : %d", vm->cycle_to_die);
	// move(14 + (vm->nb_champs * 4), 250);
	move(14, 250);
	printw("CYCLE_DELTA : %d", CYCLE_DELTA);
	// move(15 + (vm->nb_champs * 4), 250);
	move(15, 250);
	printw("NBR_LIVE : %d", vm->nbr_live);
	// move(16 + (vm->nb_champs * 4), 250);
	move(16, 250);
	printw("MAX_CHECKS : %d", MAX_CHECKS);
	move(43, 250);
	printw("nb_champs : %d", vm->nb_champs);
}

void	init_color_pairs(int nbr_champs)
{
	int		i;

	i = 0;
	while (i < nbr_champs)
	{
		init_pair(i + 1, (i % 6) + 1, 0);
		init_pair(i + 11, 0,(i % 6) + 1);
		i++;
	}
}

void	init_display(int nb_champs)
{
	WINDOW *win;

	initscr();					/* Start curses mode 		*/	
	start_color();				/* Start Colors */
	raw();						/* Line buffering disabled	*/
	noecho();					/* Don't echo() while we do getch */	
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	nodelay(stdscr, TRUE);	/* We get F1, F2 etc..		*/
	init_color_pairs(nb_champs);
}

int		display_loop(t_vm	*vm)
{
	int			key;
	int			my;
	int			mx;

	key = -1;
	getmaxyx(stdscr, my, mx);
	
	erase();
	boxAround(0, 0, SQUARE_HEIGHT, SQUARE_WIDTH);
	move(SQUARE_HEIGHT + 2, 0);
	// convert_dec_to_hex(1023);
	fill_tab(vm->ram);
	display_info(vm);
	key = getch();			/* Wait for user input */
/*	if (key == 115)
		resize_term(50, 150);*/
	move(40, 250);
	printw("key: %d", key);
	move(41, 250);
	printw("max x : %d, max y : %d", mx, my);
	
	move(42, 250);
	printw("time : %lld", clock());
	// move(43, 250);
	// printw("cycle per sec : %lld", clock()/20.0);

	refresh();			/* Print it on to the real screen */
	return (key);
}

int		display(t_vm *vm)
{
	int				key;

	key = -1;
	// getch();
	if ((key = display_loop(vm)))
	{
		if (key == KEY_NEWLINE || key == KEY_Q)
			return (0);
		if (key == KEY_PLUS && vm->speed - DELTA_SPEED > 0)
			vm->speed -= DELTA_SPEED;
		if (key == KEY_MINUS && vm->speed < SLOWEST_SPEED)
			vm->speed += DELTA_SPEED;
		if (key == KEY_SPACE)
			(vm->paused == false) ? (vm->paused = true) : (vm->paused = false);
	}
/*	env->cycles++;
	if (env->cycles == max_cycles)
	{
		max_cycles -= CYCLE_DELTA;
		env->cycles = 0;
	}*/
	return (1);
}
