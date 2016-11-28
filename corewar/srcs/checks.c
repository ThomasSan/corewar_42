/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:26:30 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/28 18:47:31 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		check_params(char opcode, char p_code[4], int p_val[4])
{
	int		i;
	
	i = 0;
	if (opcode > 15)
		return (0);
	while (i < op_tab[(int)opcode - 1].nb_arg)
	{
		if ((op_tab[(int)opcode - 1].p_type[i] >> (p_code[i] - 1)) % 2 == 0)
			return (0);
	}
}
