/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:52:36 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/15 13:06:57 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		count_pro(t_pro *pro)
{
	int		i;

	i = 0;
	while (pro)
	{
		pro = pro->next;
		i++;
	}
	return (i);
}

int		nbr_live_done(t_pro **pro)
{
	t_pro	*tmp;
	int		ret;

	ret = 0;
	if (pro && *pro)
	{
		tmp = *pro;
		while (tmp)
		{
			ret += tmp->lives;
			tmp->lives = 0;
			tmp = tmp->next;
		}
	}
	return (ret);
}

void	update_cycle_to_die(t_cycle *cycle)
{
	if (nbr_live_done(cycle->pro) >= NBR_LIVE || cycle->checks_done >= MAX_CHECKS)
	{
		cycle->cycle_to_die -= CYCLE_DELTA;
		cycle->checks_done = 0;
	}
	else
		cycle->checks_done++;
}

int		update_cycle(t_cycle *cycle, t_vm *vm)
{
	cycle->pro_nbr = count_pro(*(cycle->pro));
	if (cycle->cycles_done == cycle->cycle_to_die && cycle->dump_cycle)
	{
		while (find_dead_pro(cycle->pro))
			kill_pro(find_dead_pro(cycle->pro), vm);
		if (cycle->pro && *(cycle->pro))
		{
		cycle->cycles_done = 0;
		update_cycle_to_die(cycle);
		}
		else
			return (0);
		if (cycle->cycle_to_die <= 0)
			return (0);
	}
	else if (cycle->dump_cycle == 0)
		return (0);
	else
	{
		cycle->cycles_done++;
		if (cycle->dump_cycle != -1)
			cycle->dump_cycle--;
		return (1);
	}
	return (1);
}
