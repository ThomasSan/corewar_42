/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 12:16:39 by cchameyr          #+#    #+#             */
/*   Updated: 2016/11/30 12:17:09 by cchameyr         ###   ########.fr       */
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
	ft_printf("----- CONTENT PROG -----\n");
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
}
