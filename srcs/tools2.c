/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 15:02:30 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/22 16:09:12 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			check_p_val(char *reg)
{
	char	array[4];

	array[0] = reg[0];
	array[1] = 0;
	array[2] = 0;
	array[3] = 0;
	if (*(int*)array > 0 && *(int*)array < REG_NUMBER + 1)
		return (1);
	return (0);
}

void		copy_registre(t_process *pro, int new, int old)
{
	pro->reg[new][0] = pro->reg[old][0];
	pro->reg[new][1] = pro->reg[old][1];
	pro->reg[new][2] = pro->reg[old][2];
	pro->reg[new][3] = pro->reg[old][3];
}

int			idx_ram(int idx)
{
	if (idx >= 0)
		return (idx % MEM_SIZE);
	else
		return (MEM_SIZE - (ABS(idx) % MEM_SIZE));
}

void		move_pc(t_process *pro, int new)
{
	while (new)
	{
		pro->pc += SIGN(new);
		if (pro->pc < 0)
			pro->pc = MEM_SIZE - 1;
		else if (pro->pc >= MEM_SIZE)
			pro->pc = 0;
		new -= SIGN(new);
	}
}
