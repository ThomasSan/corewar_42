/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chmps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:54:26 by cchameyr          #+#    #+#             */
/*   Updated: 2016/12/14 13:46:20 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int		get_header(unsigned char buff[MAX_COR_SIZE], t_champ *champ)
{
	if (champ->len < sizeof(t_header))
	{
		ft_putstr("ERROR - Header corrupted !\n");
		return (0);
	}
	ft_memcpy(&champ->header, buff, sizeof(t_header));
	champ->header.magic = ft_bswap32(champ->header.magic);
	champ->header.prog_size = ft_bswap32(champ->header.prog_size);
	if (champ->header.magic != COREWAR_EXEC_MAGIC)
		return (ft_printf("ERROR - Bad magic code\n"));
	if (champ->header.prog_name[PROG_NAME_LENGTH - 1] != 0)
		return (ft_printf("ERROR - Program name is too long\n"));
	if (champ->header.comment[COMMENT_LENGTH - 1] != 0)
		return (ft_printf("ERROR - Comment is too long\n"));
	if (champ->len - sizeof(t_header) != champ->header.prog_size)
		return (ft_printf("ERROR - Pg size and real Pg size are different\n"));
	return (0);
}

void			get_champ(t_vm *vm, t_champ *champ, char *path)
{
	int				fd;
	int				i;
	unsigned char	buff[MAX_COR_SIZE];

	i = -1;
	while (++i < MAX_COR_SIZE)
		buff[i] = 0;
	champ->number = vm->nb_champ;
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_printf("ERROR - Cant read the source file :\n[%s]\n", path);
		exit_corewar(vm);
	}
	vm->champs[vm->nb_champ].len = read(fd, buff, MAX_COR_SIZE);
	close(fd);
	if (get_header(buff, champ) != 0)
		exit_corewar_msg(vm, "Failed to read champion !\n");
	champ->len -= sizeof(t_header);
	if (champ->len > CHAMP_MAX_SIZE)
		exit_corewar_msg(vm, "ERROR - Program is too long\n"
				"Faled to read champion !\n");
	ft_memcpy(champ->data, &buff[sizeof(t_header)], champ->len);
}
