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

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(-1);
}

int		check_number(t_lst *lst, t_lst *elem, int number)
{
	t_process	*pro;

	if (elem == NULL)
		return (number);
	pro = (t_process*)elem->data;
	if (pro->numero == number)
		return (check_number(lst, lst, number + 1));
	else
		return (check_number(lst, elem->next, number));
}

void	create_champion(t_vm *vm, char *name, int number)
{
	t_process	*pro;
	static int	order = 0;

	if (vm->nbr_champs >= MAX_PLAYERS)
		ft_error("Too many champions");
	number = check_number(vm->lst_champs, vm->lst_champs, number);
	pro = read_file_content(name, number, vm, order);
	pro->order = order;
	pro->inside = -1;
	pro->c = &(vm->champ[order]);
	vm->champ[order].pc_number = 1;
	vm->champ[order].first_pc = pro;
	order++;
	create_process(vm, pro);
	vm->nbr_champs += 1;
}

void	check_args(int ac, char **av, t_vm *vm)
{
	int		i;
	int		tmp;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp("-d", av[i]))
		{
			if (i >= ac - 1 || !ft_isint(av[i + 1], &tmp) || tmp < 0)
				ft_error("-d needs to be followed by an int");
			vm->cycle_to_exec = tmp;
			i++;
		}
		else if (!ft_strcmp("-n", av[i]))
		{
			if (i >= ac - 2 || !ft_isint(av[i + 1], &tmp))
				ft_error("-n needs to be followed by an int");
			create_champion(vm, av[i + 2], tmp);
			i += 2;
		}
		else if (!ft_strcmp("-g", av[i]))
			vm->o_graphic = 1;
		else if (!ft_strcmp("-s", av[i]))
			vm->print_live = 0;
		else
			create_champion(vm, av[i], 1);
	}
}

int		main(int ac, char **av)
{
	t_vm		*vm;
	int			fight;

	if (ac <= 1)
		ft_error("ERROR: Bad arg number");
	vm = boot_vm();
	check_args(ac, av, vm);
	if (vm->nbr_champs <= 0)
		ft_error("ERROR: Bad champ nbr");
	place_champions(vm);
	fight = 1;
	if (vm->o_graphic)
		init_display(vm->nbr_champs);
	while ((fight = start_fight(vm)))
		;
	if (vm->o_graphic)
		endwin();
	ft_printf("Player  %d(%s) won\n", vm->champ[vm->last_alive].id,
					vm->champ[vm->last_alive].name);
	return (0);
}
