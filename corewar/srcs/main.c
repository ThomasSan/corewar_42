/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:44:24 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/15 15:58:25 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			(*g_exec_op[17])(t_vm *vm, t_process *pr, char p_code[4]
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



int				main(int argc, char **argv)
{
	t_vm		vm;

	init_vm(&vm);
	if (get_arg(&vm, argc, argv) == -1)
		exit_corewar_msg(&vm, "help:\n-g : use displayer\n");
	init_start(&vm);
	display_debug_champ(vm.champs, 0);
	display_debug_champ(vm.champs, 1);
	display_debug_champ(vm.champs, 2);
	display_debug_champ(vm.champs, 3);
	start_battle(&vm);
	exit_corewar(&vm);
}
