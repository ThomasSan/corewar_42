/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 15:53:30 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/22 15:58:50 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			c_int(char *arr)
{
	char		c_int[4];

	c_int[0] = arr[0];
	c_int[1] = arr[1];
	c_int[2] = arr[2];
	c_int[3] = arr[3];
	return (*((int*)c_int));
}

int			c_int_rev(char *arr)
{
	char		c_int[4];

	c_int[0] = arr[3];
	c_int[1] = arr[2];
	c_int[2] = arr[1];
	c_int[3] = arr[0];
	return (*((int*)c_int));
}

short int	c_short_int(char *arr)
{
	char		c_int[2];

	c_int[0] = arr[1];
	c_int[1] = arr[0];
	return (*((short int*)c_int));
}

int			c_single_int(char tab)
{
	char		c_int[4];

	c_int[0] = tab;
	c_int[1] = 0;
	c_int[2] = 0;
	c_int[3] = 0;
	return (*((int*)c_int));
}
