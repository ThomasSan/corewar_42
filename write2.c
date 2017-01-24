/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:43:46 by tsanzey           #+#    #+#             */
/*   Updated: 2017/01/24 17:01:39 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include "op.h"
#include <unistd.h>

int		write_in_file(char *str, int fd, int i)
{
	int j;

	j = 0;
	while (str[j])
	{
		write(fd, &str[j], 1);
		j++;
		if ((i + j) % (4 * 8) == 0)
			write(fd, "\n", 1);
		if ((i + j) % 4 == 0 && (i + j) % (4 * 8) != 0)
			write(fd, " ", 1);
	}
	return (i + j);
}

void	write_magic(int fd)
{
	int		magic;

	magic = COREWAR_EXEC_MAGIC;
	magic = ((magic >> 24) & 0xff) | ((magic << 8) & 0xff0000) |
	((magic >> 8) & 0xff00) | ((magic << 24) & 0xff000000);
	write(fd, (char*)&magic, 4);
}
