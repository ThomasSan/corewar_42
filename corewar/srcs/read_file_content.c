/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 16:39:54 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/19 16:59:36 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		bendian_lendian(char *ram, int len)
{
	int		i;
	int		tmp;

	i = 0;
	while (i < len / 2)
	{
		tmp = ram[i];
		ram[i] = ram[len - i - 1];
		ram[len - i - 1] = tmp;
		i++;
	}
}

void		stock_in_r1(t_process *pro)
{
	int		i;
	char	*tmp;
	int		number;

	i = -1;
	number = pro->numero;
	tmp = (char*)&number;
	while (++i < REG_SIZE && i < 4)
		pro->reg[0][i] = tmp[i];
}

void		check_header(int fd, char *file)
{
	char			buff[4];
	unsigned int	*number;

	if (read(fd, buff, 4) != 4)
		ft_error("Failed to read");
	bendian_lendian(buff, 4);
	number = (unsigned int*)buff;
	if (*number != COREWAR_EXEC_MAGIC)
		ft_error("wrong magic number");
}

void		read_cor_file(int fd, t_process *pro, char *file, int i)
{
	char			buff[4];
	t_vm			*vm;
	unsigned int	*tmp;

	vm = pro->vm;
	if (read(fd, vm->champ[i].name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		ft_error("Bad prog_name length");
	if (read(fd, buff, 4) != 4)
		ft_error("Failed to read");
	if (read(fd, buff, 4) != 4)
		ft_error("Failed to read");
	bendian_lendian(buff, 4);
	tmp = (unsigned int*)buff;
	vm->champ[i].size = *tmp;
	if (vm->champ[i].size > CHAMP_MAX_SIZE)
		ft_error("Champ size too long");
	if (read(fd, vm->champ[i].comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		ft_error("Bad comment length");
	if (read(fd, buff, 4) != 4)
		ft_error("Failed to read");
	if (read(fd, vm->champ[i].memory, vm->champ[i].size) != vm->champ[i].size)
		ft_error("Bad memory");
}

t_process	*read_file_content(char *file, int number, t_vm *vm, int i)
{
	int			fd;
	t_process	*pro;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Can't open the file");
	check_header(fd, file);
	pro = ft_memalloc(sizeof(t_process));
	pro->vm = vm;
	read_cor_file(fd, pro, file, i);
	pro->numero = number;
	vm->champ[i].id = number;
	vm->champ[i].dead = 0;
	stock_in_r1(pro);
	return (pro);
}
