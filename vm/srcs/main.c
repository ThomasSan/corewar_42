/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 20:11:48 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 19:56:10 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			corewar_end(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->nbr_champs)
		free(vm->champs[i++].data);
	free(vm->champs);
	free(vm->ram);
	free(vm);
}

void			(*g_exec_op[17])(t_vm *vm, t_pro *pro, char p_code[4]
		, int p_val[4]) =
{
	ft_live,
	ft_ld,
	ft_st,
	ft_add,
	ft_sub,
	ft_and,
	ft_or,
	ft_xor,
	ft_zjmp,
	ft_ldi,
	ft_sti,
	ft_fork,
	ft_lld,
	ft_lldi,
	ft_lfork,
	ft_aff
};


void		ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit (-1);
}

int			main(int ac, char **av)
{
	t_vm		*vm;

	vm = NULL;
	vm = boot_vm(vm, ac, av);
	if (vm == NULL)
		ft_error("Failed to boot VM");
	start_fight(vm);
	corewar_end(vm);
	return (0);
}
