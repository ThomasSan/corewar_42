/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:45:09 by cchameyr          #+#    #+#             */
/*   Updated: 2016/11/30 17:17:57 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static t_ram		*init_ram(void)
{
	t_ram	*ram;
	int		i;

	ram = (t_ram *)ft_memalloc(sizeof(t_ram) * (MEM_SIZE + 1));
	i = -1;
	while (++i <= MEM_SIZE)
	{
		ram[i].value = 0x00;
		ram[i].owner = 0;
		ram[i].executed = 0;
	}
	return (ram);
}

static t_champ		*init_champ()
{
	t_champ		*champs;
	int			c;
	int			i;

	champs = (t_champ *)ft_memalloc(sizeof(t_champ) * MAX_PLAYERS);
	c = -1;
	while (++c <= MAX_PLAYERS)
	{
		i = -1;
		while (++i < MAX_COR_SIZE)
			champs[c].data[i] = 0;
		champs[c].pos = -1;
	}
	return (champs);
}

void				init_vm(t_vm *vm)
{
	vm->champs = init_champ();
	vm->ram = init_ram();
	vm->process = NULL;
	vm->nb_champ = 0;
	vm->option_graph = 0;
}
