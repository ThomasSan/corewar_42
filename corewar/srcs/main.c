/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:44:24 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/25 13:44:34 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				main(int argc, char **argv)
{
	t_vm	vm;

	init_vm(&vm);
	if (get_arg(&vm, argc, argv) == -1)
	{
		ft_printf("help:\n-n : use displayer\n");
		exit_corewar(&vm);
	}
	return (0);
}
