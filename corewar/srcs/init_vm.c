/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:45:09 by cchameyr          #+#    #+#             */
/*   Updated: 2016/11/30 12:34:12 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static t_ram	*init_ram(void)
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

t_champ			*init_champ()
{
	t_champ		*champs;
	int			i;
	int			i2;

	champs = (t_champ *)ft_memalloc(sizeof(t_champ) * MAX_PLAYERS);
	i = -1;
	while (++i <= MAX_PLAYERS)
	{
		i2 = -1;
		while (++i2 < MAX_COR_SIZE)
			champs->data[i] = 0;
	}
	return (champs);
}

void			init_vm(t_vm *vm)
{
	vm->champs = init_champ();
	vm->ram = init_ram();
	vm->nb_champ = 0;
	vm->option_graph = 0;
}
