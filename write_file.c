/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:43:46 by tsanzey           #+#    #+#             */
/*   Updated: 2016/12/29 16:43:48 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include "op.h"
#include <unistd.h>
#include <stdio.h>

void	write_file_len(int file_len, int fd)
{
	file_len = ((file_len >> 24) & 0xff) | ((file_len << 8) & 0xff0000) |
	((file_len >> 8) & 0xff00) | ((file_len << 24) & 0xff000000);
	write(fd, (char*)&file_len, 4);
}

int		get_size(int type, char *op)
{
	if (type == REG)
		return (1);
	if (type == IND)
		return (2);
	if (type == DIR)
		return (label_sizes(op));
	return (0);
}

int		fill_tmp(t_champ *head, char *tmp, char *op, int len)
{
	int		size;

	size = get_size(head->type, op);
	if (size == 0)
		error_and_exit(-1, NULL);
	if (size == 1)
		tmp[len] = ((size_t)head->value) % 256;
	if (size == 2)
	{
		tmp[len] = ((size_t)head->value) / 256;
		tmp[len + 1] = ((size_t)head->value) % 256;
	}
	if (size == 4)
	{
		tmp[len] = ((size_t)head->value) / (256 * 256 * 256);
		tmp[len + 1] = (((size_t)head->value) - tmp[len] * 256 * 256 * 256)
			/ (256 * 256);
		tmp[len + 2] = (((size_t)head->value) - tmp[len + 1] * 256 * 256) / 256;
		tmp[len + 3] = (((size_t)head->value) - tmp[len + 2] * 256) % 256;
	}
	return (len + size);
}

void	write_commands(t_champ *head, int fd, int len)
{
	char	tmp[14];
	char	*op;

	while (head)
	{
		if (head->type == OP)
		{
			if (len)
				write(fd, tmp, len);
			len = 0;
			tmp[len] = head->value;
			len++;
			if (head->encoding)
			{
				tmp[len] = head->encoding;
				len++;
			}
			op = head->line;
		}
		else if (head->type == REG ||
		head->type == DIR || head->type == IND)
			len = fill_tmp(head, tmp, op, len);
		head = head->next;
	}
	write(fd, tmp, len);
}

void	write_program(t_prog *prog, t_champ *head)
{
	int		fd;
	char	tmp_name[PROG_NAME_LENGTH + 4];
	char	tmp_comment[COMMENT_LENGTH + 4];

	if ((fd = open(prog->file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		error_and_exit(-1, NULL);
	write_magic(fd);
	ft_strncpy(tmp_name, prog->name, PROG_NAME_LENGTH + 4);
	ft_strncpy(tmp_comment, prog->comment, COMMENT_LENGTH + 4);
	write(fd, tmp_name, PROG_NAME_LENGTH + 4);
	write_file_len(prog->size, fd);
	write(fd, prog->comment, COMMENT_LENGTH + 4);
	write_commands(head, fd, 0);
}
