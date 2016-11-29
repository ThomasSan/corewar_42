/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:55:29 by cchameyr          #+#    #+#             */
/*   Updated: 2016/11/29 13:46:58 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	exit_corewar_msg(t_vm *vm, char *msg)
{
	ft_putstr(msg);
	exit_corewar(vm);
}

void	exit_corewar(t_vm *vm)
{
	ft_memdel((void **)&vm->ram);
	exit(0);
}
