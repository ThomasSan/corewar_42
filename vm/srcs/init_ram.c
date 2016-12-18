/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ram.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 21:41:03 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/14 21:41:39 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_ram		*init_ram(void)
{
	t_ram	*ram;
	int		i;

	i = 0;
	ram = (t_ram*)malloc(sizeof(t_ram) * MEM_SIZE);
	if (ram == NULL)
		ft_error("Allocation failed mamen");
	return (ram);
}
