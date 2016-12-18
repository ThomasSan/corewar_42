/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 21:23:17 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/14 21:33:05 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

unsigned char	*read_file(char *fn, t_champs *champs)
{
	int		fd;
	int		ret;
	unsigned char	buf[BUFF_SIZE + 1];
	unsigned char	*result;

	if ((fd = open(fn, O_RDONLY)) < 0)
		ft_error("Failed to open the file");
	champs->len = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		champs->len += ret;
	result = (unsigned char*)malloc(sizeof(unsigned char) * (champs->len + 1));
	lseek(fd, 0, SEEK_SET);
	read(fd, result, champs->len);
	result[champs->len] = '\0';
	close(fd);
	return (result);
}

void			read_prog(unsigned char *data, t_champs *champs)
{
	champs->len -= sizeof(t_header);
	if (champs->len > CHAMP_MAX_SIZE)
		ft_error("Program is too long");
	champs->data = (unsigned char*)malloc(sizeof(unsigned char) * champs->len);
	ft_memcpy(champs->data, data + sizeof(t_header), champs->len);
}

void			read_header(unsigned char *data, t_champs *champs)
{
	if ((unsigned long)champs->len < sizeof(t_header))
		ft_error("Failed to read champs : Bad file");
	ft_memcpy(&champs->header, data, sizeof(t_header));
	champs->header.prog_size = bswap_32(champs->header.prog_size);
	champs->header.magic = bswap_32(champs->header.magic);
	if (champs->header.magic != COREWAR_EXEC_MAGIC)
		ft_error("No corewar magic nbr");
	if (champs->header.prog_name[PROG_NAME_LENGTH - 1] != 0)
		ft_error("Program name too long");
	if (champs->header.comment[COMMENT_LENGTH - 1] != 0)
		ft_error("Comment too long");
	if (champs->len - sizeof(t_header) != champs->header.prog_size)
		ft_error("Prog size != real Prog size");
}
