/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:26:30 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/28 22:07:11 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op		op_tab[17];

int		check_params(char opcode, char p_code[4], int p_val[4])
{
	int		i;
	
	i = 0;
	if (opcode > 15)
		return (0);
	while (i < op_tab[(int)opcode - 1].nb_arg)
	{
//		if ((op_tab[(int)opcode - 1].p_type[i] >> (p_code[i] - 1)) % 2 == 0)
//			return (0);
//			f
	}
	return (1);
}
