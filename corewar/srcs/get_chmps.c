/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chmps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:54:26 by cchameyr          #+#    #+#             */
/*   Updated: 2016/11/25 17:25:36 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	get_champ(t_vm *vm, t_champ *champ, char *path)
{
	int		fd;

	champ->number = vm->nb_champ + 1;
	fd = open(path, O_RDONLY);
	vm->champs[vm->nb_champ].len = read(fd, champ->data, MAX_COR_SIZE);
	close(fd);
	//reste a coder la suite LOLILOL signé pepito
}
