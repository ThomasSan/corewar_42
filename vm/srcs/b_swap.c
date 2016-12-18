/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_swap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 21:34:13 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/14 21:37:45 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

unsigned short	bswap_16(unsigned short value)
{
	return ((value >> 8) | (value << 8));
}

unsigned int	bswap_32(unsigned int value)
{
	return (bswap_16(value & 0xffff) << 16) | (bswap_16(value >> 16));
}
