/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 20:46:52 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/14 21:21:56 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			count_champs(t_vm *vm)
{
	int		i;
	int		number;

	i = 0;
	number = 0;
	while (vm->av[i] != NULL)
	{
		if (ft_strstr(vm->av[i], ".cor\0") != NULL)
			number++;
		i++;
	}
	if (number > MAX_PLAYERS)
		ft_error("Too many champions");
	if (number == 0)
		ft_error("No .cor fil found");
	return (number);
}

void		put_champs_on_map(t_vm **vm)
{
	int		i;
	int		j;

	j = 0;
	while (j < (*vm)->nbr_champs)
	{
		i = 0;
		(*vm)->champs[j].position = ((j * MEM_SIZE) / (*vm)->nbr_champs);
		(*vm)->ram[(*vm)->champs[j].position].execute = 1;
		while (i < (*vm)->champs[j].len)
		{
			(*vm)->ram[(*vm)->champs[j].position + i].value = (*vm)->champs[j].data[i];
			(*vm)->ram[(*vm)->champs[j].position + i].champ = j + 1;
			i++;
		}
		j++;
	}
}	

t_champs	fill_map_with_champ(char *fn)
{
	unsigned char	*data;
	t_champs		champs;

	data = read_file(fn, &champs);
	read_header(data, &champs);
	read_prog(data, &champs);
	free(data);
	return (champs);
}

t_champs	*init_champs(t_vm *vm)
{
	t_champs	*champs;
	int			i;
	int			number;
	int			def;

	i = 0;
	def = 0;
	champs = malloc(sizeof(t_champs) * (vm->nbr_champs + 1));
	while (vm->av[i])
	{
		if (ft_strcmp(vm->av[i], "-n") == 0)
		{
			number = (vm->av[i + 1] != NULL) ? ft_atoi(vm->av[i + 1]) : def + 1;
			i += 2;
		}
		else
			number = (def + 1) * -1;
		champs[def] = fill_map_with_champ(vm->av[i]);
		champs[def].number = number;
		i++;
		def++;
	}
	return (champs);
}
