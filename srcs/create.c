/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 16:54:21 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/20 17:57:48 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			compare_pro(void *c1, void *c2)
{
	t_process *pro1;
	t_process *pro2;

	pro1 = (t_process*)c1;
	pro2 = (t_process*)c2;
	return (pro2->number - pro1->number);
}

void		create_process(t_vm *vm, t_process *pro)
{
	static int number = 0;
	t_lst		*new;

	pro->number = number;
	number++;
	new = ft_lstnew_noalloc(pro, sizeof(t_process));
	ft_lstadd_sorted(&vm->lst_champs, new, compare_pro);
}
