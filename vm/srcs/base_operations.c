/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 13:15:03 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/15 13:17:39 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

char		*ft_base16(unsigned char number)
{
	long unsigned int	div;
	int					mod;
	char				*convert;
	int					i;

	i = 0;
	convert = ft_strnew(11);
	div = number;
	while (div != 0)
	{
		div = number / 16;
		mod = number / 16;
		number = div;
		if (mod > 9)
			convert[i++] = mod + 87;
		else
			convert[i++] = mod + 48;
	}
	convert = ft_strrev(convert);
	return (convert[0] == 0 ? "0" : convert);
}
